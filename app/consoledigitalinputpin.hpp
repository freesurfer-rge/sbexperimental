#pragma once

#include <string>

#include "digitalinputpin.hpp"

namespace Signalbox {
  class ConsolePinManager;

  class ConsoleDigitalInputPin : public DigitalInputPin {
  public:
    virtual bool Get() const override;

    void Set(const bool level);
  private:
    friend class ConsolePinManager;

    ConsoleDigitalInputPin() :
      DigitalInputPin(),
      state(false),
      id() {}

    bool state;
    std::string id;
  };
}
