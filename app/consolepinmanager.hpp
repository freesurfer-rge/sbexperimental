#pragma once
#include <map>
#include <memory>
#include <sstream>

#include "pinmanager.hpp"

#include "consoledigitaloutputpin.hpp"
#include "consoledigitalinputpin.hpp"

namespace Signalbox {
  class ConsolePinManager : public PinManager {
  public:
    ConsolePinManager() :
      outputPins() {}
    
    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override;
    
    virtual DigitalInputPin* CreateDigitalInputPin(const std::string pinId) override;
  private:
    std::map<std::string,std::unique_ptr<ConsoleDigitalOutputPin>> outputPins;
    std::map<std::string,std::unique_ptr<ConsoleDigitalInputPin>> inputPins;

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
