#pragma once

#include "pinmanager.hpp"
#include "mappinmanager.hpp"

#include "mockdigitaloutputpin.hpp"
#include "mockdigitalinputpin.hpp"
#include "mockpwmchannel.hpp"

namespace Signalbox {
  class MockPinManager : public MapPinManager<std::string,MockDigitalInputPin,MockDigitalOutputPin> {
  public:
    MockPinManager() :
      MapPinManager(),
      pwmChannels() {}

    virtual void Initialise( const std::vector<I2CDeviceData>& i2cDevices ) override;
    
    MockDigitalOutputPin* FetchMockDigitalOutputPin(const std::string pinId) const;
    
    MockDigitalInputPin* FetchMockDigitalInputPin(const std::string pinId) const;

    MockPWMChannel* FetchMockPWMChannel(const DeviceRequestData& data) const;
    
    size_t DigitalOutputPinCount() const {
      return this->getOutputPinCount();
    }
    
    size_t DigitalInputPinCount() const {
      return this->getInputPinCount();
    }

    size_t PWMChannelCount() const {
      return this->pwmChannels.size();
    }

    virtual PWMChannel* CreatePWMChannel(const DeviceRequestData& data) override;
  protected:
    virtual std::string parsePinId( const std::string idString ) const override;
    virtual void setupInputPin( MockDigitalInputPin* pin, const DigitalInputPinData& data ) const override;

  private:
    std::map<std::string,std::unique_ptr<MockPWMChannel>> pwmChannels;
    
    std::string getKey(const DeviceRequestData& data) const {
      return data.controller + data.controllerData;
    }
  };
}
