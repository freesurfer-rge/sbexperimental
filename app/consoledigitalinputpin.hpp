#pragma once

#include <string>

#include "digitalinputpin.hpp"

namespace Signalbox {
  class ConsolePinManager;

  class ConsoleDigitalInputPin : public DigitalInputPin {
  public:
    ConsoleDigitalInputPin() :
      DigitalInputPin(),
      state(false),
      id() {}
    
    virtual bool Get() const override;

    void Set(const bool level);
  private:
    friend class ConsolePinManager;

    bool state;
    std::string id;
  };
}
