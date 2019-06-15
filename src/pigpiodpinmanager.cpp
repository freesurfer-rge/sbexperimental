#include <sstream>
#include <stdexcept>
#include <iostream>

#include <pigpiod_if2.h>

#include "pigpiodpca9685.hpp"

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
    piId(-1),
    devices(),
    hpr() {
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

  void PiGPIOdPinManager::Initialise(const std::vector<I2CDeviceData>& i2cDevices) {
    for( auto it=i2cDevices.begin();
	 it != i2cDevices.end();
	 ++it ) {
      // Create the next device
      std::unique_ptr<I2CDevice> nxtDevice;
      if( (*it).kind == "pca9685" ) {
	nxtDevice = std::unique_ptr<I2CDevice>( new PiGPIOdPCA9685( (*it).name,
								    (*it).bus,
								    (*it).address ) );
	auto pca9685 = dynamic_cast<PiGPIOdPCA9685*>(nxtDevice.get());
	pca9685->piId = this->piId;
	pca9685->Register(&(this->hpr));
      } else {
	std::stringstream msg;
	msg << "Specified device kind '"
	    << (*it).kind
	    << "' not recognised";
	throw std::out_of_range(msg.str());
      }

      nxtDevice->Initialise((*it).settings);

      this->devices.push_back(std::move(nxtDevice));
    }
  }
  
  PWMChannel* PiGPIOdPinManager::CreatePWMChannel(const DeviceRequestData& data) {
    auto channelProvider = this->hpr.GetPWMChannelProvider( data.controller );
    return channelProvider->GetPWMChannel( data.controllerData,
					   data.settings );
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

    const std::string glitchSetting = "glitch";
    if( data.settings.count(glitchSetting) == 1 ) {
      unsigned int usecFilter = std::stoul(data.settings.at(glitchSetting));

      err = set_glitch_filter(pin->piId, pin->pinId, usecFilter);
      if( err != 0 ) {
	std::stringstream msg;
	msg << "set_glitch_filter failed for"
	    << " Pi: " << pin->piId
	    << " pin: " << pin->pinId
	    << " error: " << err;
	throw std::runtime_error(msg.str());
      }
    }

    const std::string pudSetting = "pudResistor";
    if( data.settings.count(pudSetting) == 1 ) {
      unsigned int pud;
      const std::string pudVal = data.settings.at(pudSetting);
      
      if( pudVal == "up" ) {
	pud = PI_PUD_UP;
      } else if( pudVal == "down" ) {
	pud = PI_PUD_DOWN;
      } else if( pudVal == "off" ) {
	pud = PI_PUD_OFF;
      } else {
	std::stringstream msg;
	msg << "pudResistor setting '"
	    << pudVal
	    << "' not recognised"
	    << std::endl;
	throw std::runtime_error(msg.str());
      }

      err = set_pull_up_down(pin->piId, pin->pinId, pud );
      if( err != 0 ) {
	std::stringstream msg;
	msg << "set_pull_up_down failed for"
	    << " Pi: " << pin->piId
	    << " pin: " << pin->pinId
	    << " error: " << err;
	throw std::runtime_error(msg.str());
      }
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
