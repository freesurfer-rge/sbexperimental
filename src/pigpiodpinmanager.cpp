#include <sstream>
#include <stdexcept>
#include <iostream>

#include <pigpiod_if2.h>

#include "pigpiodpinmanager.hpp"

namespace Signalbox {
  // Note that this is not an owning pointer
  PiGPIOdPinManager* PiGPIOdPinManager::singleton = NULL;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
  void PiGPIOdPinManager::callBackDispatch(int pi,
					   unsigned int user_gpio,
					   unsigned int level,
					   uint32_t tick) {
    if( pi != singleton->piId ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": Bad pi = " << pi;
      throw std::runtime_error(msg.str());
    }

    auto dip = singleton->getInputPin(user_gpio);
    dip->NotifyOneUpdate();
  }
#pragma GCC diagnostic pop
  
  PiGPIOdPinManager::PiGPIOdPinManager() :
    MapPinManager(),
    piId(-1) {
    if( PiGPIOdPinManager::singleton != NULL ) {
      throw std::runtime_error("PiGPIOdPinManager already exists");
    }
    
    this->piId = pigpio_start(NULL, NULL);
    if( this->piId < 0 ) {
      std::stringstream msg;
      msg << "Could not connect to pigpiod."
	  << "Have you run 'sudo pigpiod' ?";
      throw std::runtime_error(msg.str());
    }
    PiGPIOdPinManager::singleton = this;
  }

  PiGPIOdPinManager::~PiGPIOdPinManager() {
    this->clearAllPins();
    if( this->piId >= 0 ) {
      pigpio_stop(this->piId);
    }
    PiGPIOdPinManager::singleton = NULL;
  }
  
  int PiGPIOdPinManager::parsePinId(const std::string pinId) const {
    // Format is GPIOnn
    int pin = std::stoi(pinId.substr(4,2));

    return pin;
  }
  
  void PiGPIOdPinManager::setupInputPin( PiGPIOdDigitalInputPin* pin, const DigitalInputPinData& data ) const {
    pin->piId = this->piId;
    pin->pinId = this->parsePinId(data.id);

    int err = set_mode(pin->piId, pin->pinId, PI_INPUT);
    if( err != 0 ) {
      std::stringstream msg;
      msg << "set_mode failed for Pi: "
	  << pin->piId
	  << " pin: " << pin->pinId
	  << " error: " << err;
      throw std::runtime_error(msg.str());
    }

    int callbackId = callback(this->piId,pin->pinId, EITHER_EDGE, &PiGPIOdPinManager::callBackDispatch );
    if( (callbackId==pigif_bad_malloc) ||
	(callbackId==pigif_duplicate_callback) ||
	(callbackId==pigif_bad_callback) ) {
      std::stringstream msg;
      msg << "callback failed for Pi: "
	  << pin->piId
	  << " pin: " << pin->pinId
	  << " error: " << callbackId;
      throw std::runtime_error(msg.str());
    }
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
