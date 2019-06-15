#include <sstream>
#include <stdexcept>

#include "mockpca9685.hpp"

namespace Signalbox {
  void MockPCA9685::Initialise( const std::map<std::string,std::string>& settings ) {
    const std::string refClockSetting = "referenceClock";
    const std::string pwmFreqSetting = "pwmFrequency";

    if( settings.count(refClockSetting) != 1 ) {
      std::stringstream msg;
      msg << "Settings for MockPCA9685 did not contain " << refClockSetting;
      throw std::out_of_range(msg.str());
    }
    if( settings.count(pwmFreqSetting) != 1 ) {
      std::stringstream msg;
      msg << "Settings for MockPCA9685 did not contain " << pwmFreqSetting;
      throw std::out_of_range(msg.str());
    }

    this->referenceClock = std::stod(settings.at(refClockSetting));
    this->pwmFrequency = std::stod(settings.at(pwmFreqSetting));

    if( this->referenceClock <= 0 ) {
      throw std::out_of_range("referenceClock must be positive"); 
    }
    if( this->pwmFrequency <= 0 ) {
      throw std::out_of_range("pwmFrequency must be positive");
    }
  }

  PWMChannel* MockPCA9685::GetPWMChannel( const std::string channelId,
					  const std::map<std::string,std::string> settings ) {
    if( settings.size() > 0 ) {
      throw std::out_of_range("settings not supported in MockPCA9685::GetPWMChannel");
    }
    
    const unsigned int channel = std::stoul(channelId);
    if( channel >= 16 ) {
      throw std::out_of_range("channelId must be in range [0,15]");
    }

    if( this->assignedChannels.count(channel) != 0 ) {
      std::stringstream msg;
      msg << "Channel " << channel << " is already assigned";
      throw std::out_of_range(msg.str());
    }

    auto nxtChannel = std::unique_ptr<MockPWMChannel>( new MockPWMChannel );
    nxtChannel->controller = this->name;
    nxtChannel->controllerData = channelId;
    this->assignedChannels[channel] = std::move(nxtChannel);

    return this->assignedChannels[channel].get();
  }

  void MockPCA9685::Register(HardwareProviderRegistrar* registrar) {
    registrar->RegisterPWMChannelProvider( this->name, this );
  }
}
