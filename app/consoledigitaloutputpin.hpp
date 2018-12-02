#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class ConsolePinManager;
  
  class ConsoleDigitalOutputPin : public DigitalOutputPin {
  public:
    virtual void Set(const bool level ) override;

    virtual bool Get() const override;
  private:
    friend class ConsolePinManager;

    ConsoleDigitalOutputPin() :id() {}

    std::string id;
  };
}
