#pragma once

#include <string>

#include "pwmchannel.hpp"

namespace Signalbox {
  class MockPinManager;
  
  class MockPWMChannel : public PWMChannel {
  public:
    MockPWMChannel() :
      controller("Did not set"),
      controllerData("Left unset"),
      state(0) {}

    virtual void Set(const unsigned int value ) override;

    virtual unsigned int Get() const override;

    std::string controller;
    std::string controllerData;
  private:
    friend MockPinManager;

    unsigned int state;
  };
}
