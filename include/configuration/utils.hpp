#pragma once

#include <memory>
#include <string>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "configuration/xercesstringdeleter.hpp"

namespace Signalbox {
  namespace Configuration {
    std::unique_ptr<XMLCh,xercesstringdeleter> StrToXMLCh( const std::string& str );
    std::string XMLChToStr( const XMLCh* xmlChars );

    xercesc::DOMElement* GetSingleElementByName( const xercesc::DOMElement* parent, const std::string name );

    std::string GetSingleElementTextByName( const xercesc::DOMElement* parent, const std::string name );
    
    std::string GetAttributeByName( const xercesc::DOMElement* element, const std::string name );
    
    std::string GetIdAttribute( const xercesc::DOMElement* element );

    bool IsElementNode( const xercesc::DOMNode* node );
    
    bool IsOutputPin( const xercesc::DOMElement* element );
    bool IsInputPin( const xercesc::DOMElement* element );
  }
}
