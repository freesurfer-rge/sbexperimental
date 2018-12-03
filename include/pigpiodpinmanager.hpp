#pragma once
#include <map>

#include "pinmanager.hpp"

#include "pigpioddigitaloutputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager : public PinManager {
  public:
    PiGPIOdPinManager() :
      outputPins() {
    }

    ~PiGPIOdPinManager() {

    }

    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override;

    int ParseId(const std::string pinId) const;

    // Remove copy constructor and operator=
    PiGPIOdPinManager(PiGPIOdPinManager&) = delete;
    PiGPIOdPinManager& operator=(PiGPIOdPinManager&) = delete;
  private:
    std::map<int,std::unique_ptr<PiGPIOdDigitalOutputPin>> outputPins;

  };
}
