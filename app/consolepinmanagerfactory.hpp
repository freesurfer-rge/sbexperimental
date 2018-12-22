#pragma once

#include "pinmanagerfactory.hpp"

#include "consolepinmanager.hpp"

namespace Signalbox {
  class ConsolePinManagerFactory : public PinManagerFactory {
  public:
    ConsolePinManagerFactory() : cpm() {}
    
    virtual std::unique_ptr<PinManager> Create() override {
      if( this->cpm != NULL ) {
	throw std::runtime_error("Tried to create second ConsolePinManager");
      }
      auto res = std::unique_ptr<PinManager>(new ConsolePinManager());
      this->cpm = dynamic_cast<ConsolePinManager*>(res.get());
      if( this->cpm == NULL ) {
	throw std::runtime_error("Failed to cast back to ConsolePinManager");
      }
      
      return res;
    }

    ConsolePinManager* cpm;

    // Delete copy constructor and operator= due to pointer member
    ConsolePinManagerFactory(ConsolePinManagerFactory&) = delete;
    ConsolePinManagerFactory& operator=(ConsolePinManagerFactory&) = delete;
  };
}
