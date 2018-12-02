#pragma once

#include "outputpin.hpp"

namespace Signalbox {
  class ConsoleOutputPin : public OutputPin {
  public:
    ConsoleOutputPin() : pin(std::string("UNASSIGNED")) {}

    std::string pin;

    virtual void TurnOn() override;

    virtual void TurnOff() override;

  protected:
    virtual std::unique_ptr<OutputPin> manufacture(const std::string pindId) override;
  };
}
