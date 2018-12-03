#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager;

  class PiGPIOdDigitalOutputPin : public DigitalOutputPin {
  public:
    virtual void Set(const bool level) override;

    virtual bool Get() const override;
  private:
    friend class PiGPIOdPinManager;

    PiGPIOdDigitalOutputPin() {}
  };
}
