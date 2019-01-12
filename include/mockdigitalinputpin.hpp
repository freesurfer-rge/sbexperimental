#pragma once

#include "digitalinputpin.hpp"

namespace Signalbox {
  class MockPinManager;

  class MockDigitalInputPin : public DigitalInputPin {
  public:
    MockDigitalInputPin() :
      DigitalInputPin(),
      state(false) {}
    
    virtual bool Get() const override;

    void Set(const bool level);
  private:
    friend class MockPinManager;

    bool state;
  };
}
