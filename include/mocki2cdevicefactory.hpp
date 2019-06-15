#pragma once

#include <set>
#include <utility>

#include "i2cdevicefactory.hpp"

namespace Signalbox {
  class MockI2CDeviceFactory : public I2CDeviceFactory {
  public:
    MockI2CDeviceFactory() :
      I2CDeviceFactory(),
      deviceNames(),
      deviceBusAddresses() {}
    
    virtual ~MockI2CDeviceFactory() {}

    virtual std::unique_ptr<I2CDevice> CreateDevice(const I2CDeviceData& data) override;
  private:
    std::set<std::string> deviceNames;
    std::set<std::pair<unsigned int,unsigned int>> deviceBusAddresses;
  };
}
