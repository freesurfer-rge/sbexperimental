#pragma once

#include <string>

#include <xercesc/dom/DOMElement.hpp>

namespace Signalbox {
  class DigitalOutputPinData {
  public:
    DigitalOutputPinData() :
      id(),
      control() {}

    std::string id;
    std::string control;
  };
}
