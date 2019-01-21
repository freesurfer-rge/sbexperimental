#pragma once

#include <string>

#include <xercesc/dom/DOMElement.hpp>

namespace Signalbox {
  class DigitalOutputPinData {
  public:
    DigitalOutputPinData( const xercesc::DOMElement* xmlElement );

    std::string getId() const;

    std::string getControl() const;
    
  private:
    std::string id;
    std::string control;
  };
}
