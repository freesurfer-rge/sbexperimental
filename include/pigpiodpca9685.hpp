#pragma once

#include <memory>

#include "pwmchannelprovider.hpp"
#include "i2cdevice.hpp"
#include "pca9685pwmchannel.hpp"

namespace Signalbox {
  class PiGPIOdPCA9685 : public I2CDevice, public PWMChannelProvider {
    PiGPIOdPCA9685( const std::string deviceName,
		    const unsigned int bus,
		    const unsigned int address ) :
      I2CDevice(deviceName,bus,address),
      piId(-1),
      deviceHandle(-1),
      referenceClock(-1),
      pwmFrequency(-1),
      assignedChannels() {}

    virtual ~PiGPIOdPCA9685();
    
    virtual void Initialise( const std::map<std::string,std::string>& settings ) override;

    virtual PWMChannel* GetPWMChannel( const std::string channelId,
				       const std::map<std::string,std::string> settings ) override;

    virtual void Register(HardwareProviderRegistrar* registrar) override;

    int piId;
    int deviceHandle;
    double referenceClock;
    double pwmFrequency;

    std::map<unsigned int,std::unique_ptr<PCA9685PWMChannel>> assignedChannels;

    unsigned char StartRegister(const unsigned char channel) const;
    unsigned char StopRegister(const unsigned char channel) const;

    void CheckChannel(const unsigned char channel) const;
  private:
    const int registerMODE1 = 0x00;
    const int registerPRESCALE = 0xfe;
    const unsigned char channels = 16;
  };
}
