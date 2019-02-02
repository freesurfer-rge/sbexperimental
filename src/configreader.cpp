#include <sstream>

#include <boost/filesystem.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "configuration/utils.hpp"
#include "configuration/xercesstringdeleter.hpp"

#include "configreader.hpp"

#include "digitaloutputpindata.hpp"
#include "signalheaddata.hpp"

namespace Signalbox {
  
  ConfigReader::ConfigReader( const std::string& filename ) : XercesGuard(),
							      configFileParser() {
    if( !boost::filesystem::exists(filename) ) {
      throw std::runtime_error( filename + " NOT FOUND" );
    }

    this->configFileParser = std::unique_ptr<xercesc::XercesDOMParser>(new xercesc::XercesDOMParser);

    // Configure the parser
    this->configFileParser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
    this->configFileParser->setDoNamespaces( false );
    this->configFileParser->setDoSchema( false );
    this->configFileParser->setLoadExternalDTD( false );

    this->configFileParser->parse( filename.c_str() );
  }

  void ConfigReader::ReadRailTrafficControl( RailTrafficControlData& rtcData ) {
    // Get the root element of the document
    xercesc::DOMElement* elementSignalbox = this->GetSignalBoxElement();

    auto TAG_RailTrafficControl = Configuration::GetTranscoded("RailTrafficControl");
    auto TAG_Host = Configuration::GetTranscoded("Host");
    auto TAG_Port = Configuration::GetTranscoded("Port");

    auto elementListRTC = elementSignalbox->getElementsByTagName( TAG_RailTrafficControl.get() );
    if( elementListRTC == nullptr ) {
      throw std::runtime_error("No elementListRTC");
    }
    if( elementListRTC->getLength() != 1 ) {
      throw std::runtime_error("Found multiple RailTrafficControl tags");
    }

    auto rtcElement = dynamic_cast<xercesc::DOMElement*>(elementListRTC->item(0));
    if( rtcElement == nullptr ) {
      throw std::runtime_error("Failed to obtain rtcElement");
    }

    // Fetch the host data
    auto elementListHost = rtcElement->getElementsByTagName( TAG_Host.get() );
    if( elementListHost == nullptr ) {
      throw std::runtime_error("No elementListHost");
    }
    if( elementListHost->getLength() != 1 ) {
      throw std::runtime_error("Found multiple Host tags");
    }

    auto hostElement = dynamic_cast<xercesc::DOMElement*>(elementListHost->item(0));
    if( hostElement == nullptr ) {
      throw std::runtime_error("Failed to obtain hostElement");
    }

    // Apparently there are issues with getTextContent, but I don't see an alternative
    auto host = hostElement->getTextContent();
    if( host == nullptr ) {
      throw std::runtime_error("Failed to call hostElement->getTextContent()" );
    }
    auto hostChars = std::unique_ptr<char,Configuration::xercesstringdeleter>(xercesc::XMLString::transcode(host),
									      Configuration::xercesstringdeleter());
    rtcData.host = std::string(hostChars.get());

    // On to the port
    auto elementListPort = rtcElement->getElementsByTagName( TAG_Port.get() );
    if( elementListPort == nullptr ) {
      throw std::runtime_error("No elementListPort");
    }
    if( elementListPort->getLength() != 1 ) {
      throw std::runtime_error("Found multiple Port tags");
    }
    auto portElement = dynamic_cast<xercesc::DOMElement*>(elementListPort->item(0));
    if( portElement == nullptr ) {
      throw std::runtime_error("Failed to obtain portElement");
    }

    // Skate around issues with getTextContent
    auto port = portElement->getTextContent();
    if( port == nullptr ) {
      throw std::runtime_error("Failed to call hostElement->getTextContent()");
    }
    auto portChars = std::unique_ptr<char,Configuration::xercesstringdeleter>(xercesc::XMLString::transcode(port),
									      Configuration::xercesstringdeleter());

    auto portString = std::string(portChars.get());
    rtcData.port = std::stoul(portString);
  }
  
  void ConfigReader::ReadControlledItems( std::vector<std::unique_ptr<ControlledItemData>>& items ) {
    // Make sure we have an empty list
    items.clear();

    // Get the root element of the document
    xercesc::DOMElement* elementSignalbox = this->GetSignalBoxElement();
    
    auto TAG_ControlledItems = Configuration::GetTranscoded("ControlledItems");
    auto TAG_SignalHead = Configuration::GetTranscoded("SignalHead");
    
    auto elementListControlledItems = elementSignalbox->getElementsByTagName( TAG_ControlledItems.get() );
    if( elementListControlledItems == nullptr ) {
      throw std::runtime_error("No elementListControlledItem");
    }
    if( elementListControlledItems->getLength() != 1 ) {
      throw std::runtime_error("Bad element count in elementListControlledItem");
    }

    auto elementControlledItems = elementListControlledItems->item(0);
    if( elementControlledItems == nullptr ) {
      throw std::runtime_error("No elementControlledItem");
    }

    auto controlledItems = elementControlledItems->getChildNodes();
    for( XMLSize_t i=0; i<controlledItems->getLength(); ++i ) {
      std::unique_ptr<ControlledItemData> item(nullptr);
      auto currentNode = controlledItems->item(i);

      if( Configuration::IsElementNode(currentNode) ) {
	// Cast node to an element
	auto currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
	
	if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_SignalHead.get() ) ) {
	  item.reset( this->ReadSignalHead(currentElement) );

	} else {
	  throw std::runtime_error("Unknown tag name");
	}
	
	// Common code to sort out the id attribute
	item->id.Parse(Configuration::GetIdAttribute(currentElement));
      }
      
      // Add to the list
      if( item.get() != nullptr ) {
	// Have to 'move' since we can't copy a unique_ptr
	items.push_back(std::move(item));
      }
    }
  }
  
  xercesc::DOMElement* ConfigReader::GetSignalBoxElement() {
    auto TAG_SignalBox = Configuration::GetTranscoded("SignalBox");
    
    // The following remains owned by the parser object
    auto xmlDoc = this->configFileParser->getDocument();

    auto docElement = xmlDoc->getDocumentElement();
    if( docElement == nullptr ) {
      throw std::runtime_error("Empty document");
    }

    if( !xercesc::XMLString::equals(docElement->getTagName(), TAG_SignalBox.get()) ) {
      throw std::runtime_error("Root element is not SignalBox");
    }

    return docElement;
  }
  
  ControlledItemData* ConfigReader::ReadSignalHead(xercesc::DOMElement* currentElement ) {
    std::unique_ptr<SignalHeadData> signal( new SignalHeadData );

    auto aspectCount_attr = Configuration::GetAttributeByName(currentElement, "aspectCount");
    signal->aspectCount = std::stoi(aspectCount_attr);
    
    auto outputPins = currentElement->getChildNodes();
    // For some reason, the length of this list is 9.....
    for( XMLSize_t iPin=0; iPin<outputPins->getLength(); iPin++ ) {
      auto pinNode = outputPins->item(iPin);
      
      if( Configuration::IsElementNode(pinNode) ) {
	// Cast node to an element
	auto currentPin = dynamic_cast<xercesc::DOMElement*>(pinNode);
	
	if( Configuration::IsOutputPin(currentPin) ) {
	  DigitalOutputPinData pin(currentPin);
    
	  auto controlPin = StringToSignalHeadPins(pin.getControl());	  
	  signal->pinData[controlPin] = pin.getId();
	}
      }
    }
    
    // This gets the raw pointer, and stops the unique_ptr from managing it
    return signal.release();
  }
}
