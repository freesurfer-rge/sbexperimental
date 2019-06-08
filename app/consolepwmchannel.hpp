#pragma once

#include <string>

#include "pwmchannel.hpp"

namespace Signalbox {
  class ConsolePinManager;
  
  class ConsolePWMChannel : public PWMChannel {
  public:
    ConsolePWMChannel() : state(0) {}

    virtual void Set(const unsigned int value ) override;

    virtual unsigned int Get() const override;

    std::string controller;
    std::string controllerData;
  private:
    friend ConsolePinManager;

    unsigned int state;
  };
}
