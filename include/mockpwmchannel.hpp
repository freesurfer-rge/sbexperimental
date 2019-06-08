#pragma once

#include "pwmchannel.hpp"

namespace Signalbox {
  class MockPinManager;
  
  class MockPWMChannel : public PWMChannel {
  public:
    MockPWMChannel() : state(0) {}

    virtual void Set(const unsigned int value ) override;

    virtual unsigned int Get() const override;

  private:
    friend MockPinManager;

    unsigned int state;
  };
}
