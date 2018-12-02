#pragma once
#include <map>
#include <atomic>

#include "outputpin.hpp"

namespace Signalbox {
  class MockOutputPin : public OutputPin {
  public:
    MockOutputPin() : pin(std::string("UNASSIGNED")), isOn(false) {}
    
    std::string pin;

    std::atomic<bool> isOn;
    
    virtual void TurnOn() override;

    virtual void TurnOff() override;

    static std::map<std::string,MockOutputPin*> allPins;

  protected:
    virtual std::unique_ptr<OutputPin> manufacture(const std::string pinId) override;
  };
}
