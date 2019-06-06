#pragma once

#include <vector>

#include "i2cdevicedata.hpp"

namespace Signalbox {
  class I2CBusData {
  public:
    I2CBusData() : devices() {}
    
    std::vector<I2CDeviceData> devices;
  };
}
