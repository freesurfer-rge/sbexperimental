#pragma once

#include <memory>
#include <string>

namespace Signalbox {
  class OutputPin {
  public:
    virtual ~OutputPin() {}
    
    virtual void TurnOn() = 0;

    virtual void TurnOff() = 0;
    
    static std::unique_ptr<OutputPin> create(const std::string pinId);

    static std::unique_ptr<OutputPin> sample;
    
  protected:
    virtual std::unique_ptr<OutputPin> manufacture(const std::string pinId) = 0;
  };
}
