#pragma once

#include <string>

#include "digitaloutputpin.hpp"
#include "digitalinputpin.hpp"

#include "digitalinputpindata.hpp"

namespace Signalbox {
  class PinManager {
  public:
    virtual ~PinManager() {}

    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) = 0;

    virtual DigitalInputPin* CreateDigitalInputPin(const DigitalInputPinData& data) = 0;
  };
}
