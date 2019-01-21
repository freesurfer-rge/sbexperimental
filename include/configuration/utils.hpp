#pragma once

#include <memory>
#include <string>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "configuration/xercesstringdeleter.hpp"

namespace Signalbox {
  namespace Configuration {
    std::unique_ptr<XMLCh,xercesstringdeleter> GetTranscoded( const std::string& str );

    std::string GetAttributeByName( const xercesc::DOMElement* element, const std::string name );
    
    std::string GetIdAttribute( const xercesc::DOMElement* element );
    
    bool IsOutputPin( const xercesc::DOMElement* element );
  }
}