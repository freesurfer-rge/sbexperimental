#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager;

  class PiGPIOdDigitalOutputPin : public DigitalOutputPin {
  public:
    virtual void Set(const bool level) override;

    virtual bool Get() const override;

    // Delete copy constructor and operator=
    PiGPIOdDigitalOutputPin(PiGPIOdDigitalOutputPin&) = delete;
    PiGPIOdDigitalOutputPin& operator=(PiGPIOdDigitalOutputPin&) = delete;
  private:
    friend class PiGPIOdPinManager;

    PiGPIOdDigitalOutputPin() :
      piId(-1),
      pinId(-1) {}

    PiGPIOdDigitalOutputPin(const int pi, const int pin);

    const int piId;

    const int pinId;
  };
}
