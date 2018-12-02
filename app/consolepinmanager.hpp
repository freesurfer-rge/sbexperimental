#pragma once
#include <map>
#include <memory>

#include "pinmanager.hpp"

#include "consoledigitaloutputpin.hpp"

namespace Signalbox {
  class ConsolePinManager : public PinManager {
  public:
    ConsolePinManager() :
      outputPins() {}
    
    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override;

  private:
    std::map<std::string,std::unique_ptr<ConsoleDigitalOutputPin>> outputPins;
  };
}
