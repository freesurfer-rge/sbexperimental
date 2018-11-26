#pragma once

#include "outputpin.hpp"

namespace Signalbox {
  class ConsoleOutputPin : public OutputPin {
  public:
    ConsoleOutputPin() : pin(-1) {}

    char pin;

    virtual void TurnOn() override;

    virtual void TurnOff() override;

  protected:
    virtual std::unique_ptr<OutputPin> manufacture(const char pindId) override;
  };
}
