#pragma once

#include "digitalinputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager;

  class PiGPIOdDigitalInputPin : public DigitalInputPin {
  public:
    PiGPIOdDigitalInputPin() :
      DigitalInputPin() {}
    
    virtual bool Get() const override;

    PiGPIOdDigitalInputPin(const PiGPIOdDigitalInputPin&) = delete;
    PiGPIOdDigitalInputPin& operator=(const PiGPIOdDigitalInputPin&) = delete;

  private:
    friend class PiGPIOdPinManager;
  };
}
