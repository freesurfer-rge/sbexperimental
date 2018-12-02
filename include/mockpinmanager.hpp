#pragma once

#include <map>

#include "pinmanager.hpp"

#include "mockdigitaloutputpin.hpp"

namespace Signalbox {
  class MockPinManager : PinManager {
  public:
    MockPinManager() :
      outputPins() {}
    
    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override;

  private:
    std::map<std::string,MockDigitalOutputPin> outputPins;
  };
}
