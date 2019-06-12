#pragma once

#include "i2cdevicefactory.hpp"

namespace Signalbox {
  class MockI2CDeviceFactory : public I2CDeviceFactory {
  public:
    virtual ~MockI2CDeviceFactory() {}

    virtual std::unique_ptr<I2CDevice> CreateDevice(const I2CDeviceData& data) override;
  };
}
