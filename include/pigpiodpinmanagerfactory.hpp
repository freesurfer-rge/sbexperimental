#pragma once

#include "pinmanagerfactory.hpp"

#include "pigpiodpinmanager.hpp"

namespace Signalbox {
  class PiGPIOdPinManagerFactory : public PinManagerFactory {
  public:
    PiGPIOdPinManagerFactory() {}
    
    virtual std::unique_ptr<PinManager> Create() override {
      return std::unique_ptr<PinManager>(new PiGPIOdPinManager());
    }

    // Delete copy constructor and operator= due to pointer member
    PiGPIOdPinManagerFactory(PiGPIOdPinManagerFactory&) = delete;
    PiGPIOdPinManagerFactory& operator=(PiGPIOdPinManagerFactory&) = delete;
  };
}
