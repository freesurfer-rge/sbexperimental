#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager;

  class PiGPIOdDigitalOutputPin : public DigitalOutputPin {
  public:
    PiGPIOdDigitalOutputPin() :
      DigitalOutputPin(),
      piId(-1),
      pinId(-1) {}
    
    virtual void Set(const bool level) override;

    virtual bool Get() const override;
    
    ~PiGPIOdDigitalOutputPin() {
      this->Set(false);
    }

    // Delete copy constructor and operator=
    PiGPIOdDigitalOutputPin(PiGPIOdDigitalOutputPin&) = delete;
    PiGPIOdDigitalOutputPin& operator=(PiGPIOdDigitalOutputPin&) = delete;
  private:
    friend class PiGPIOdPinManager;

    int piId;

    int pinId;
  };
}
