#pragma once

#include "digitalinputpin.hpp"

namespace Signalbox {
  class MockPinManager;

  class MockDigitalInputPin : public DigitalInputPin {
  public:
    virtual bool Get() const override;

    void Set(const bool level);
  private:
    friend class MockPinManager;

    MockDigitalInputPin() :
      DigitalInputPin(),
      state(false) {}

    bool state;
  };
}
