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

#include "signalheaddata.hpp"

namespace Signalbox {
  
  ConfigReader::ConfigReader( const std::string& filename ) : configFileParser(),
							      ATTR_id(),
							      ATTR_aspectCount(),
							      TAG_OutputPin(),
							      ATTR_OutputPin_control() {
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

    this->ATTR_id = Configuration::GetTranscoded("id");

    this->ATTR_aspectCount = Configuration::GetTranscoded("aspectCount");

    this->TAG_OutputPin = Configuration::GetTranscoded("OutputPin");
    this->ATTR_OutputPin_control = Configuration::GetTranscoded("control");
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

      if( (currentNode->getNodeType()) &&
	  (currentNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE ) ) {
	// Cast node to an element
	auto currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
	
	if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_SignalHead.get() ) ) {
	  item.reset( this->ReadSignalHead(currentElement) );

	} else {
	  throw std::runtime_error("Unknown tag name");
	}
	
	// Common code to sort out the id attribute
	auto id_attr = currentElement->getAttribute(this->ATTR_id.get());
	auto idchars = std::unique_ptr<char,Configuration::xercesstringdeleter>(xercesc::XMLString::transcode(id_attr),Configuration::xercesstringdeleter());
	item->id.Parse(std::string(idchars.get()));
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

    auto aspectCount_attr = currentElement->getAttribute(this->ATTR_aspectCount.get());
    if( xercesc::XMLString::stringLen(aspectCount_attr) > 0 ) {
      signal->aspectCount = xercesc::XMLString::parseInt(aspectCount_attr);
    }
    
    auto outputPins = currentElement->getChildNodes();
    // For some reason, the length of this list is 9.....
    for( XMLSize_t iPin=0; iPin<outputPins->getLength(); iPin++ ) {
      auto pinNode = outputPins->item(iPin);
      
      if( (pinNode->getNodeType()) &&
	  (pinNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE ) ) {
	// Cast node to an element
	auto currentPin = dynamic_cast<xercesc::DOMElement*>(pinNode);
	
	if( xercesc::XMLString::equals(currentPin->getTagName(), this->TAG_OutputPin.get() ) ) {
	  this->ReadSignalHeadOutputPin( currentPin, signal.get() );
	}
      }
    }
    
    // This gets the raw pointer, and stops the unique_ptr from managing it
    return signal.release();
  }

  void ConfigReader::ReadSignalHeadOutputPin( xercesc::DOMElement* currentPin, SignalHeadData* signal ) {
    auto id_attr = currentPin->getAttribute(this->ATTR_id.get());
    auto idchars = std::unique_ptr<char,Configuration::xercesstringdeleter>(xercesc::XMLString::transcode(id_attr),Configuration::xercesstringdeleter());
	  
    auto idstring = std::string(idchars.get());
	  
    auto control_attr = currentPin->getAttribute(this->ATTR_OutputPin_control.get());
    auto controlchars = std::unique_ptr<char,Configuration::xercesstringdeleter>(xercesc::XMLString::transcode(control_attr),Configuration::xercesstringdeleter());
    auto controlstring = std::string(controlchars.get());
    
    auto controlPin = StringToSignalHeadPins(controlstring);
	  	  
    signal->pinData[controlPin] = idstring;
  }
  
}
