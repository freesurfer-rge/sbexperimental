#include <sstream>
#include <stdexcept>

#include "mockpca9685.hpp"

#include "mocki2cdevicefactory.hpp"

namespace Signalbox {
  std::unique_ptr<I2CDevice> MockI2CDeviceFactory::CreateDevice(const I2CDeviceData& data) {
    std::unique_ptr<I2CDevice> result;

    if( data.kind == "pca9685" ) {
      result = std::unique_ptr<I2CDevice>(new MockPCA9685(data.name, data.bus, data.address));
    } else {
      std::stringstream msg;
      msg << "Specified device kind '"
	  << data.kind
	  << "' not recognised";
      throw std::out_of_range(msg.str());
    }

    result->Initialise(data.settings);
    
    return result;
  }
}
