#pragma once

#include <string>
#include <map>

#include "hardwareprovider.hpp"

namespace Signalbox {
  class I2CDevice : public HardwareProvider {
  public:
    I2CDevice( const std::string deviceName,
	       const unsigned int bus,
	       const unsigned int address ) :
      name(deviceName),
      i2cBus(bus),
      i2cAddress(address) {}

    virtual ~I2CDevice() {}

    virtual void Initialise( const std::map<std::string,std::string>& settings )= 0;
    
    const std::string name;
    const unsigned int i2cBus;
    const unsigned int i2cAddress;
  };
}
