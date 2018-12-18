#pragma once

#include "pinmanagerfactory.hpp"

#include "mockpinmanager.hpp"

namespace Signalbox {
  class MockPinManagerFactory : public PinManagerFactory {
  public:
    MockPinManagerFactory() : mpm() {}
    
    virtual std::unique_ptr<PinManager> Create() override {
      if( this->mpm != NULL ) {
	throw std::runtime_error("Tried to create second MockPinManager");
      }
      auto res = std::unique_ptr<PinManager>(new MockPinManager());
      this->mpm = dynamic_cast<MockPinManager*>(res.get());
      if( this->mpm == NULL ) {
	throw std::runtime_error("Failed to cast back to MockPinManager");
      }
      
      return res;
    }

    MockPinManager* mpm;
  };
}
