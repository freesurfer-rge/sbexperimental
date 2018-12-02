#pragma once

namespace Signalbox {
  class DigitalOutputPin {
  public:
    virtual ~DigitalOutputPin() {}

    virtual void Set(const bool level) = 0;

    virtual bool Get() const = 0;

    void TurnOn() {
      this->Set(true);
    }

    void TurnOff() {
      this->Set(false);
    }
  };
}
