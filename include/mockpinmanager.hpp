#pragma once

#include <map>
#include <memory>

#include "pinmanager.hpp"
#include "mappinmanager.hpp"

#include "mockdigitaloutputpin.hpp"
#include "mockdigitalinputpin.hpp"

namespace Signalbox {
  class MockPinManager : public MapPinManager<std::string,MockDigitalInputPin,MockDigitalOutputPin> {
  public:
    MockPinManager() :
      MapPinManager() {}
    
    MockDigitalOutputPin* FetchMockDigitalOutputPin(const std::string pinId) const;
    
    MockDigitalInputPin* FetchMockDigitalInputPin(const std::string pinId) const;
    
    size_t DigitalOutputPinCount() const {
      return this->getOutputPinCount();
    }
    
    size_t DigitalInputPinCount() const {
      return this->getInputPinCount();
    }

  protected:
    virtual std::string parsePinId( const std::string idString ) const override;

    virtual void setupInputPin( MockDigitalInputPin* pin, const std::string pinId ) const override;

    virtual void setupOutputPin( MockDigitalOutputPin* pin, const std::string pinId ) const override;
    
  };
}
