#include <sstream>
#include <stdexcept>
#include <iostream>

#include <pigpiod_if2.h>

#include "pigpiodpinmanager.hpp"

namespace Signalbox {
  bool PiGPIOdPinManager::exists = false;
  
  PiGPIOdPinManager::PiGPIOdPinManager() :
      piId(-1),
      outputPins() {
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
    this->outputPins.clear();
    if( this->piId >= 0 ) {
      pigpio_stop(this->piId);
    }
    PiGPIOdPinManager::exists = false;
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
