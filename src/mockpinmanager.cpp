#include <sstream>
#include <stdexcept>

#include "mockpinmanager.hpp"

#include "mocki2cdevicefactory.hpp"

namespace Signalbox {

  void MockPinManager::Initialise( const std::vector<I2CDeviceData>& i2cDevices ) {
    MockI2CDeviceFactory devFactory;

    for( auto it=i2cDevices.begin();
	 it!=i2cDevices.end();
	 ++it ) {
      auto nxtDevice = devFactory.CreateDevice(*it);

      nxtDevice->Register(&(this->hpr));

      this->devices.push_back(std::move(nxtDevice));
    }
  }
  
  MockDigitalOutputPin* MockPinManager::FetchMockDigitalOutputPin(const std::string pinId) const {
    return this->getOutputPin(pinId);
  }

  MockDigitalInputPin* MockPinManager::FetchMockDigitalInputPin(const std::string pinId) const {
    return this->getInputPin(pinId);
  }

  MockPWMChannel* MockPinManager::FetchMockPWMChannel(const DeviceRequestData& data) const {
    return this->pwmChannels.at(this->getKey(data)).get();
  }

  PWMChannel* MockPinManager::CreatePWMChannel(const DeviceRequestData& data) {
    if( this->pwmChannels.count(this->getKey(data)) != 0 ) {
      std::stringstream msg;
      msg << "PWMChannel '" << this->getKey(data) << "' already exists";
      throw std::runtime_error(msg.str());
    }
    auto nxt = std::unique_ptr<MockPWMChannel>(new MockPWMChannel);
    nxt->controller = data.controller;
    nxt->controllerData = data.controllerData;

    this->pwmChannels[this->getKey(data)] = std::move(nxt);

    return this->pwmChannels[this->getKey(data)].get();
  }

  std::string MockPinManager::parsePinId( const std::string idString ) const {
    return idString;
  }
  
  void MockPinManager::setupInputPin( MockDigitalInputPin* pin, const DigitalInputPinData& data ) const {
    pin->id = data.id;
    pin->createSettings = data.settings;
  }
}
