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

    auto TAG_RailTrafficControl = std::string("RailTrafficControl");
    auto TAG_Host = std::string("Host");
    auto TAG_Port = std::string("Port");

    auto rtcElement = Configuration::GetSingleElementByName( elementSignalbox,
							     TAG_RailTrafficControl );

    // Fetch the host data
    rtcData.host = Configuration::GetSingleElementTextByName( rtcElement, TAG_Host );

    // On to the port
    auto portString = Configuration::GetSingleElementTextByName( rtcElement, TAG_Port );
    auto portNumber = std::stoul(portString);
    if( portNumber > std::numeric_limits<uint16_t>::max() ) {
      throw std::runtime_error("Invalid Port for RailTrafficControl");
    }
    rtcData.port = std::stoul(portString);
  }
  
  void ConfigReader::ReadControlledItems( std::vector<std::unique_ptr<ControlledItemData>>& items ) {
    // Make sure we have an empty list
    items.clear();

    // Get the root element of the document
    xercesc::DOMElement* elementSignalbox = this->GetSignalBoxElement();
    
    auto TAG_ControlledItems = std::string("ControlledItems");
    auto TAG_SignalHead = Configuration::StrToXMLCh("SignalHead");
    auto TAG_TrackCircuit = Configuration::StrToXMLCh("TrackCircuit");
    
    auto elementControlledItems = Configuration::GetSingleElementByName( elementSignalbox,
									 TAG_ControlledItems );

    auto controlledItems = elementControlledItems->getChildNodes();
    for( XMLSize_t i=0; i<controlledItems->getLength(); ++i ) {
      std::unique_ptr<ControlledItemData> item(nullptr);
      auto currentNode = controlledItems->item(i);

      if( Configuration::IsElementNode(currentNode) ) {
	// Cast node to an element
	auto currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
	
	if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_SignalHead.get() ) ) {
	  item.reset( this->ReadSignalHead(currentElement) );
	} else if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_TrackCircuit.get() ) ) {
	  item.reset( this->ReadTrackCircuit(currentElement) );
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
    auto TAG_SignalBox = Configuration::StrToXMLCh("SignalBox");
    
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

  ControlledItemData* ConfigReader::ReadTrackCircuit(xercesc::DOMElement* currentElement ) {
    std::unique_ptr<TrackCircuitData> tc( new TrackCircuitData );

    return tc.release();
  }
}
