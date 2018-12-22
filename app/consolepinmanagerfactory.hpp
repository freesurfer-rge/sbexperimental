#pragma once

#include "pinmanagerfactory.hpp"

#include "consolepinmanager.hpp"

namespace Signalbox {
  class ConsolePinManagerFactory : public PinManagerFactory {
  public:
    ConsolePinManagerFactory() {}
    
    virtual std::unique_ptr<PinManager> Create() override {
      return std::unique_ptr<PinManager>(new ConsolePinManager());
    }
  };
}
