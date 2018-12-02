#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class MockPinManager;

  class MockDigitalOutputPin : public DigitalOutputPin {
  public:
    virtual void Set(const bool level ) override;

    virtual bool Get() const override;

  private:
    friend class MockPinManager;
    
    MockDigitalOutputPin() : state(false) {}

    bool state;
  };
}
