#pragma once
#include <map>
#include <memory>


#include "pinmanager.hpp"

#include "pigpioddigitaloutputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager : public PinManager {
  public:
    PiGPIOdPinManager();

    ~PiGPIOdPinManager();

    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override;

    int ParseId(const std::string pinId) const;

    int GetPiId() const {
      return this->piId;
    }

    // Remove copy constructor and operator=
    PiGPIOdPinManager(PiGPIOdPinManager&) = delete;
    PiGPIOdPinManager& operator=(PiGPIOdPinManager&) = delete;
  private:
    static bool exists;
    
    int piId;
    std::map<int,std::unique_ptr<PiGPIOdDigitalOutputPin>> outputPins;
  };
}
