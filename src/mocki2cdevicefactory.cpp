#include <sstream>
#include <stdexcept>

#include "mockpca9685.hpp"

#include <iomanip>

#include "mocki2cdevicefactory.hpp"

namespace Signalbox {
  std::unique_ptr<I2CDevice> MockI2CDeviceFactory::CreateDevice(const I2CDeviceData& data) {
    std::unique_ptr<I2CDevice> result;

    
    if( this->deviceNames.count(data.name) != 0 ) {
      std::stringstream msg;
      msg << "Specified device name '"
	  << data.name
	  << "' already exists";
      throw std::out_of_range(msg.str());
    }

    auto busAddress = std::make_pair(data.bus, data.address);
    if( this->deviceBusAddresses.count(busAddress) != 0 ) {
      std::stringstream msg;
      msg << "Specified bus and address ["
	  << busAddress.first
	  << ", "
	  << std::hex << std::showbase << busAddress.second
	  << "] already assigned to a device";
      throw std::out_of_range(msg.str());
    }
    
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

    this->deviceNames.insert(data.name);
    this->deviceBusAddresses.insert(busAddress);
    return result;
  }
}
