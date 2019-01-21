#pragma once

#include <memory>
#include <string>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "configuration/xercesstringdeleter.hpp"

namespace Signalbox {
  namespace Configuration {
    std::unique_ptr<XMLCh,Configuration::xercesstringdeleter> GetTranscoded( const std::string& str );

    bool IsOutputPin( const xercesc::DOMElement* element );
  }
}
