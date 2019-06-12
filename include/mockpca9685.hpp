#pragma once

#include "pwmchannelprovider.hpp"
#include "i2cdevice.hpp"
#include "mockpwmchannel.hpp"

namespace Signalbox {
  class MockPCA9685 : public I2CDevice, public PWMChannelProvider {
  public:
    MockPCA9685( const std::string deviceName,
	         const unsigned int bus,
	         const unsigned int address ) :
      I2CDevice(deviceName,bus,address),
      referenceClock(-1),
      pwmFrequency(-1),
      assignedChannels() {}

    virtual void Initialise( const std::map<std::string,std::string>& settings ) override;

    virtual PWMChannel* GetPWMChannel( const std::string channelId,
				       const std::map<std::string,std::string> settings ) override;

    virtual void Register(HardwareProviderRegistrar* registrar) override;
    
    double referenceClock;
    double pwmFrequency;

    std::map<unsigned int,std::unique_ptr<MockPWMChannel>> assignedChannels;
  };
}
