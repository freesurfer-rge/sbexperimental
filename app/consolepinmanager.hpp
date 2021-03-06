#pragma once

#include <iostream>

#include "pinmanager.hpp"
#include "mappinmanager.hpp"

#include "consoledigitaloutputpin.hpp"
#include "consoledigitalinputpin.hpp"
#include "consolepwmchannel.hpp"

namespace Signalbox {
  class ConsolePinManager : public MapPinManager<std::string,ConsoleDigitalInputPin,ConsoleDigitalOutputPin> {
  public:
    ConsolePinManager() :
      MapPinManager(),
      pwmChannels() {}

    virtual void Initialise( const std::vector<I2CDeviceData>& i2cDevices ) override {
      std::cout << __PRETTY_FUNCTION__ << " is not yet implemented" << std::endl;
    }
    
    virtual PWMChannel* CreatePWMChannel(const DeviceRequestData& data) override;
  protected:
    virtual std::string parsePinId( const std::string idString ) const override;

    virtual void setupInputPin( ConsoleDigitalInputPin* pin, const DigitalInputPinData& data ) const override;

    virtual void setupOutputPin( ConsoleDigitalOutputPin* pin, const std::string pinId ) const override;

  private:
    std::map<std::string,std::unique_ptr<ConsolePWMChannel>> pwmChannels;
    
    std::string getKey(const DeviceRequestData& data) const {
      return data.controller + data.controllerData;
    }
  };
}
