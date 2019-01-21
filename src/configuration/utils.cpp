#include "configuration/utils.hpp"

namespace Signalbox {
  namespace Configuration {
    std::unique_ptr<XMLCh,xercesstringdeleter> GetTranscoded( const std::string& str ) {
      XMLCh* tc = xercesc::XMLString::transcode(str.c_str());
      return std::unique_ptr<XMLCh,xercesstringdeleter>(tc, xercesstringdeleter());
    }

    std::string GetAttributeByName( const xercesc::DOMElement* element, const std::string name ) {
      auto tcName = GetTranscoded(name);
      auto attr = element->getAttribute(tcName.get());
      auto attrChars = std::unique_ptr<char,xercesstringdeleter>(xercesc::XMLString::transcode(attr),
								 xercesstringdeleter());
	  
      return std::string(attrChars.get());
    }

    std::string GetIdAttribute( const xercesc::DOMElement* element ) {
      return GetAttributeByName(element, "id");
    }
    
    bool IsElementNode( const xercesc::DOMNode* node ) {
      return (node->getNodeType()) &&
	(node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE );
    }
      
    bool IsOutputPin( const xercesc::DOMElement* element ) {
      auto TAG_OutputPin = GetTranscoded("OutputPin");
      
      return xercesc::XMLString::equals(element->getTagName(), TAG_OutputPin.get());
    }
  }
}
