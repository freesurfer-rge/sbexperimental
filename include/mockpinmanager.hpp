#pragma once

#include <map>
#include <memory>

#include "pinmanager.hpp"

#include "mockdigitaloutputpin.hpp"

namespace Signalbox {
  class MockPinManager : public PinManager {
  public:
    MockPinManager() :
      outputPins() {}
    
    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override;

  private:
    std::map<std::string,std::unique_ptr<MockDigitalOutputPin>> outputPins;
  };
}
