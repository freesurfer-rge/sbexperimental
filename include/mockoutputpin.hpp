#pragma once
#include <map>
#include <atomic>

#include "outputpin.hpp"

namespace Signalbox {
  class MockOutputPin : public OutputPin {
  public:
    MockOutputPin() : pin(-1), isOn(false) {}
    
    char pin;

    std::atomic<bool> isOn;
    
    virtual void TurnOn() override;

    virtual void TurnOff() override;

    static std::map<char,MockOutputPin*> allPins;

  protected:
    virtual std::unique_ptr<OutputPin> manufacture(const char pinId) override;
  };
}
