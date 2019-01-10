#include <sstream>
#include <stdexcept>
#include <iostream>

#include <pigpiod_if2.h>

#include "pigpiodpinmanager.hpp"

namespace Signalbox {
  bool PiGPIOdPinManager::exists = false;
  
  PiGPIOdPinManager::PiGPIOdPinManager() :
    MapPinManager(),
    piId(-1) {
    if( PiGPIOdPinManager::exists ) {
      throw std::runtime_error("PiGPIOdPinManager already exists");
    }
    
    this->piId = pigpio_start(NULL, NULL);
    if( this->piId < 0 ) {
      std::stringstream msg;
      msg << "Could not connect to pigpiod."
	  << "Have you run 'sudo pigpiod' ?";
      throw std::runtime_error(msg.str());
    }
    PiGPIOdPinManager::exists = true;
  }

  PiGPIOdPinManager::~PiGPIOdPinManager() {
    this->clearAllPins();
    if( this->piId >= 0 ) {
      pigpio_stop(this->piId);
    }
    PiGPIOdPinManager::exists = false;
  }
  
  int PiGPIOdPinManager::parsePinId(const std::string pinId) const {
    // Format is GPIOnn
    int pin = std::stoi(pinId.substr(4,2));

    return pin;
  }
  
  void PiGPIOdPinManager::setupInputPin( PiGPIOdDigitalInputPin* pin, const int pinId ) const {
    throw std::runtime_error("PiGPIOdPinManager::setupInputPin not yet implemented");
  }

  void PiGPIOdPinManager::setupOutputPin( PiGPIOdDigitalOutputPin* pin, const int pinId ) const {
    pin->piId = this->piId;
    pin->pinId = pinId;
    
    int err = set_mode(pin->piId, pin->pinId, PI_OUTPUT);
    if( err != 0 ) {
      std::stringstream msg;
      msg << "set_mode failed for Pi: "
	  << pin->piId
	  << " pin: " << pin->pinId
	  << " error: " << err;
      throw std::runtime_error(msg.str());
    }
    pin->Set(false);
  }
}
