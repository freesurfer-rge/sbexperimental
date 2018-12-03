#include <sstream>
#include <stdexcept>
#include <iostream>

#include <pigpiod_if2.h>

#include "pigpiodpinmanager.hpp"

namespace Signalbox {
  PiGPIOdPinManager::PiGPIOdPinManager() :
      piId(-1),
      outputPins() {
    this->piId = pigpio_start(NULL, NULL);
      if( this->piId < 0 ) {
	std::stringstream msg;
	msg << "Could not connect to pigpiod."
	    << "Have you run 'sudo pigpiod' ?";
	throw std::runtime_error(msg.str());
      }
  }

  PiGPIOdPinManager::~PiGPIOdPinManager() {
    this->outputPins.clear();
    if( this->piId >= 0 ) {
      pigpio_stop(this->piId);
    }
  }
  
  int PiGPIOdPinManager::ParseId(const std::string pinId) const {
    // Format is GPIOnn
    int pin = std::stoi(pinId.substr(4,2));

    return pin;
  }
  
  DigitalOutputPin* PiGPIOdPinManager::CreateDigitalOutputPin(const std::string pinId) {
    const int id = this->ParseId(pinId);
    
     if( this->outputPins.count(id) != 0 ) {
      std::stringstream msg;
      msg << "Pin '" << pinId << "' already exists";
      throw std::runtime_error(msg.str());
    }

     auto nxt = std::unique_ptr<PiGPIOdDigitalOutputPin>(new PiGPIOdDigitalOutputPin(this->piId, id));
     
     this->outputPins[id] = std::move(nxt);

     return this->outputPins[id].get();
  }
}
