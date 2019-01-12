#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class MockPinManager;

  class MockDigitalOutputPin : public DigitalOutputPin {
  public:
    MockDigitalOutputPin() : state(false) {}
    
    virtual void Set(const bool level ) override;

    virtual bool Get() const override;

  private:
    friend class MockPinManager;

    bool state;
  };
}
