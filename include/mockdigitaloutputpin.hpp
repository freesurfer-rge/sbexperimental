#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class MockDigitalOutputPin : DigitalOutputPin {
  public:
    virtual void Set(const bool level ) override;

    virtual bool Get() const override;
    
  private:
    MockDigitalOutputPin() : state(false) {}

    bool state;
  };
}
