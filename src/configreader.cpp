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

  void ConfigReader::ReadConfiguration( std::vector< std::unique_ptr<ControlledItemData> >& items ) {
    // Make sure we have an empty list
    items.clear();

    auto TAG_SignalBox = Configuration::GetTranscoded("SignalBox");
    
    // The following remains owned by the parser object
    auto xmlDoc = this->configFileParser->getDocument();

    auto elementSignalbox = xmlDoc->getDocumentElement();
    if( elementSignalbox == nullptr ) {
      throw std::runtime_error("Empty document");
    }

    this->ReadControlledItems( elementSignalbox, items );
  }

  void ConfigReader::ReadControlledItems( xercesc::DOMElement* elementSignalbox,
					  std::vector<std::unique_ptr<ControlledItemData>>& items ) {
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
