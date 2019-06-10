#pragma once

#include "hardwareprovider.hpp"

namespace Signalbox {
  class I2CDevice : HardwareProvider {
  public:
    I2CDevice( const unsigned int bus,
	       const unsigned int address ) :
      i2cBus(bus),
      i2cAddress(address) {}
    
  protected:
    unsigned int i2cBus;
    unsigned int i2cAddress;
  };
}
