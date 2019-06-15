#include <sstream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <iomanip>
#include <cmath>

#include <pigpiod_if2.h>

#include "pigpiodchecker.hpp"

#include "pigpiodpca9685.hpp"

namespace Signalbox {
  PiGPIOdPCA9685::~PiGPIOdPCA9685() {
     i2c_close(this->piId, this->deviceHandle);
  }

  void PiGPIOdPCA9685::Initialise( const std::map<std::string,std::string>& settings ) {
    const std::string refClockSetting = "referenceClock";
    const std::string pwmFreqSetting = "pwmFrequency";

    if( settings.count(refClockSetting) != 1 ) {
      std::stringstream msg;
      msg << "Settings for PiGPIOdPCA9685 did not contain " << refClockSetting;
      throw std::out_of_range(msg.str());
    }
    if( settings.count(pwmFreqSetting) != 1 ) {
      std::stringstream msg;
      msg << "Settings for PiGPIOdPCA9685 did not contain " << pwmFreqSetting;
      throw std::out_of_range(msg.str());
    }

    this->referenceClock = std::stod(settings.at(refClockSetting));
    this->pwmFrequency = std::stod(settings.at(pwmFreqSetting));

    if( this->referenceClock <= 0 ) {
      throw std::out_of_range("referenceClock must be positive"); 
    }
    if( this->pwmFrequency <= 0 ) {
      throw std::out_of_range("pwmFrequency must be positive");
    }

    // Start the chip
    const int i2cFlags = 0; // Only allowed value

    this->deviceHandle = i2c_open(this->piId, this->i2cBus, this->i2cAddress, i2cFlags);
    if( this->deviceHandle < 0 ) {
      std::cerr << "i2c_open returned: " << this->deviceHandle << std::endl;
      exit(1);
    }

    // Configure the chip
    const char enableValue = 0x20;
    PIGPIOD_SAFE_CALL( i2c_write_byte_data(this->piId, this->deviceHandle,
					   PiGPIOdPCA9685::registerMODE1, enableValue) );
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    // Enable change of the prescale value
    const char enablePrescaleValue = 0x10;
    PIGPIOD_SAFE_CALL( i2c_write_byte_data(this->piId, this->deviceHandle,
					   PiGPIOdPCA9685::registerMODE1,
					   enablePrescaleValue) );
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    
    // Calculate prescale from Equation (1) of datasheet
    const unsigned char prescaleValue = round( referenceClock / 4096 / pwmFrequency ) - 1;
    std::cout << "Calculated prescale = "
	      << std::setbase(16)
	      << (unsigned int)prescaleValue
	      << std::endl;
    if( prescaleValue < 3 ) {
      throw std::invalid_argument("Calculated prescaleValue is less than 3");
    }

    // Set the prescale
    PIGPIOD_SAFE_CALL( i2c_write_byte_data(this->piId, this->deviceHandle,
					   PiGPIOdPCA9685::registerPRESCALE,
					   prescaleValue) );

    // Put the chip back into the right mode
    PIGPIOD_SAFE_CALL( i2c_write_byte_data(this->piId, this->deviceHandle,
					   PiGPIOdPCA9685::registerMODE1,
					   enableValue) );
    
    // Set all 'start' registers to 0
    for( unsigned char c=0; c < PiGPIOdPCA9685::channels; c++ ) {
      const unsigned char startRegister = this->StartRegister(c);
      PIGPIOD_SAFE_CALL( i2c_write_word_data(this->piId, this->deviceHandle,
					     startRegister, 0 ) );
    } 
  }

  unsigned char PiGPIOdPCA9685::StartRegister(const unsigned char channel) const {
    this->CheckChannel(channel);
    
    return 0x06 + (channel*4);
  }

  unsigned char PiGPIOdPCA9685::StopRegister(const unsigned char channel) const {
    this->CheckChannel(channel);

    return 0x08 + (channel*4);
  }

  void PiGPIOdPCA9685::CheckChannel(const unsigned char channel) const {
    if( channel >= PiGPIOdPCA9685::channels ) {
      throw std::out_of_range("Only have 16 channels");
    }
  }

  PWMChannel* PiGPIOdPCA9685::GetPWMChannel( const std::string channelId,
					     const std::map<std::string,std::string> settings ) {
    if( settings.size() > 0 ) {
      throw std::out_of_range("settings not supported in PiGPIOdPCA9685::GetPWMChannel");
    }
    
    const unsigned int channel = std::stoul(channelId);
    if( channel >= PiGPIOdPCA9685::channels ) {
      throw std::out_of_range("channelId must be in range [0,15]");
    }

    if( this->assignedChannels.count(channel) != 0 ) {
      std::stringstream msg;
      msg << "Channel " << channel << " is already assigned";
      throw std::out_of_range(msg.str());
    }

    auto nxtChannel = std::unique_ptr<PCA9685PWMChannel>( new PCA9685PWMChannel(this->piId, this->deviceHandle, this->StopRegister(channel)) );
    this->assignedChannels[channel] = std::move(nxtChannel);

    return this->assignedChannels[channel].get();
  }

  void PiGPIOdPCA9685::Register(HardwareProviderRegistrar* registrar) {
    registrar->RegisterPWMChannelProvider( this->name, this );
  }

}
