#include <sstream>
#include <stdexcept>

#include "mockpca9685.hpp"

#include "mocki2cdevicefactory.hpp"

namespace Signalbox {
  std::unique_ptr<I2CDevice> MockI2CDeviceFactory::CreateDevice(const I2CDeviceData& data) {
    auto result = std::unique_ptr<MockPCA9685>(new MockPCA9685(data.name, data.bus, data.address));

    result->Initialise(data.settings);
    
    return result;
  }
}
