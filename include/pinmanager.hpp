#pragma once

#include <string>

#include "digitaloutputpin.hpp"
#include "digitalinputpin.hpp"

namespace Signalbox {
  class PinManager {
  public:
    virtual ~PinManager() {}

    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) = 0;

    virtual DigitalInputPin* CreateDigitalInputPin(const std::string pinId) = 0;
  };
}
