#pragma once

#include <map>
#include <memory>

#include "pinmanager.hpp"

#include "mockdigitaloutputpin.hpp"
#include "mockdigitalinputpin.hpp"

namespace Signalbox {
  class MockPinManager : public PinManager {
  public:
    MockPinManager() :
      outputPins(),
      inputPins() {}
    
    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override;

    virtual DigitalInputPin* CreateDigitalInputPin(const std::string pinId) override;

    MockDigitalOutputPin* FetchMockDigitalOutputPin(const std::string pinId) const;

    MockDigitalInputPin* FetchMockDigitalInputPin(const std::string pinId) const;

    size_t DigitalOutputPinCount() const {
      return this->outputPins.size();
    }

    size_t DigitalInputPinCount() const {
      return this->inputPins.size();
    }

  private:
    std::map<std::string,std::unique_ptr<MockDigitalOutputPin>> outputPins;
    std::map<std::string,std::unique_ptr<MockDigitalInputPin>> inputPins;

    void checkIfPinExists( const std::string pinId ) const {
      if( this->outputPins.count(pinId) != 0 ) {
	std::stringstream msg;
	msg << "Pin '" << pinId << "' already exists as OutputPin";
	throw std::runtime_error(msg.str());
      }
      if( this->inputPins.count(pinId) != 0 ) {
	std::stringstream msg;
	msg << "Pin '" << pinId << "' already exists as InputPin";
	throw std::runtime_error(msg.str());
      }
    }
  };
}
