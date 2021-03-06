#include <sstream>
#include <iostream>

#include <xercesc/dom/DOMNodeList.hpp>

#include "configuration/utils.hpp"

namespace Signalbox {
  namespace Configuration {
    std::unique_ptr<XMLCh,xercesstringdeleter> StrToXMLCh( const std::string& str ) {
      XMLCh* tc = xercesc::XMLString::transcode(str.c_str());
      return std::unique_ptr<XMLCh,xercesstringdeleter>(tc, xercesstringdeleter());
    }

    std::string XMLChToStr( const XMLCh* xmlChars ) {
      auto chars = std::unique_ptr<char,Configuration::xercesstringdeleter>(xercesc::XMLString::transcode(xmlChars),
									    Configuration::xercesstringdeleter());
      return std::string(chars.get());
    }

    xercesc::DOMElement* GetSingleElementByName( const xercesc::DOMElement* parent, const std::string name ) {
      auto TAG_Name = StrToXMLCh(name);

      auto elementList = parent->getElementsByTagName( TAG_Name.get() );
      if( elementList == nullptr ) {
	std::stringstream msg;
	msg << "Failed getElementsByTagName call for " << name;
	throw std::runtime_error(msg.str());
      }
      
      if( elementList->getLength() != 1 ) {
	std::stringstream msg;
	msg << "Did not find exactly one child element " << name;
	throw std::runtime_error(msg.str());
      }
      
      auto result = dynamic_cast<xercesc::DOMElement*>(elementList->item(0));
      if( result == nullptr ) {
	std::stringstream msg;
	msg << "Failed to obtain item "
	    << name
	    << " from elementList";
	throw std::runtime_error(msg.str());
      }
      
      return result;
    }

    std::string GetSingleElementTextByName( const xercesc::DOMElement* parent, const std::string name ) {
      auto element = GetSingleElementByName(parent, name);

      // Apparently there are issues with getTextContent, but I don't see an alternative
      auto elementContent = element->getTextContent();
      if( elementContent == nullptr ) {
	std::stringstream msg;
	msg << "Failed call getTextContent on " << name;
	throw std::runtime_error(msg.str());
      }
            return XMLChToStr(elementContent);
    }
  
    std::string GetAttributeByName( const xercesc::DOMElement* element, const std::string name ) {
      auto tcName = StrToXMLCh(name);
      auto attr = element->getAttribute(tcName.get());
      return XMLChToStr(attr);
    }

    std::string GetIdAttribute( const xercesc::DOMElement* element ) {
      return GetAttributeByName(element, "id");
    }
    
    void PopulateSettingsMap( const xercesc::DOMElement* parent, std::map<std::string,std::string>& settings ) {
      auto children = parent->getChildNodes();

      auto TAG_Setting = Configuration::StrToXMLCh("Setting");
      
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);

	if( Configuration::IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);

	  if( xercesc::XMLString::equals( element->getTagName(), TAG_Setting.get() ) ) {
	    std::string key = GetAttributeByName( element, "key" );
	    std::string value = GetAttributeByName( element, "value" );
	    
	    settings[key] = value;
	  }
	}
      }
    }
    
    bool IsElementNode( const xercesc::DOMNode* node ) {
      return (node->getNodeType()) &&
	(node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE );
    }
      
    bool IsOutputPin( const xercesc::DOMElement* element ) {
      auto TAG_OutputPin = StrToXMLCh("OutputPin");
      
      return xercesc::XMLString::equals(element->getTagName(), TAG_OutputPin.get());
    }

    bool IsInputPin( const xercesc::DOMElement* element ) {
      auto TAG_InputPin = StrToXMLCh("InputPin");

      return xercesc::XMLString::equals(element->getTagName(), TAG_InputPin.get());
    }

    bool IsPWMChannel( const xercesc::DOMElement* element ) {
      auto TAG_PWMChannel = StrToXMLCh("PWMChannel");

      return xercesc::XMLString::equals(element->getTagName(), TAG_PWMChannel.get());
    }
  }
}
