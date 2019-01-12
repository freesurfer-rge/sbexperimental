#pragma once

#include "digitaloutputpin.hpp"

namespace Signalbox {
  class ConsolePinManager;
  
  class ConsoleDigitalOutputPin : public DigitalOutputPin {
  public:
    ConsoleDigitalOutputPin() : id() {}
    
    virtual void Set(const bool level ) override;

    virtual bool Get() const override;
  private:
    friend class ConsolePinManager;

    std::string id;
  };
}
