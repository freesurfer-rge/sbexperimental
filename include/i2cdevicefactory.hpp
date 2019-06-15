#pragma once

#include <memory>

#include "i2cdevicedata.hpp"
#include "i2cdevice.hpp"

namespace Signalbox {
  class I2CDeviceFactory {
  public:
    virtual ~I2CDeviceFactory() {}

    virtual std::unique_ptr<I2CDevice> CreateDevice(const I2CDeviceData& data) = 0;
  };
}
