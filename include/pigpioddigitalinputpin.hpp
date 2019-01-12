#pragma once

#include "digitalinputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager;

  class PiGPIOdDigitalInputPin : public DigitalInputPin {
  public:
    PiGPIOdDigitalInputPin() :
      DigitalInputPin(),
      piId(-1),
      pinId(-1) {}
    
    virtual bool Get() const override;

    PiGPIOdDigitalInputPin(const PiGPIOdDigitalInputPin&) = delete;
    PiGPIOdDigitalInputPin& operator=(const PiGPIOdDigitalInputPin&) = delete;

  private:
    friend class PiGPIOdPinManager;

    int piId;

    int pinId;
  };
}
