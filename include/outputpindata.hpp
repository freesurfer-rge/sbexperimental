#pragma once

#include <string>

#include <xercesc/dom/DOMElement.hpp>

namespace Signalbox {
  class OutputPinData {
  public:
    OutputPinData( const xercesc::DOMElement* xmlElement );

    std::string getId() const;

    std::string getControl() const;
    
  private:
    std::string id;
    std::string control;
  };
}
