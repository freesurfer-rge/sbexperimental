#pragma once

#include <string>

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class PinManager {
  public:
    virtual ~PinManager() {}

    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pidId) = 0;
  };
}
