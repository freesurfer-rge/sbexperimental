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
    std::stringstream msg;
    msg << __PRETTY_FUNCTION__
	<< " not implemented";
    throw std::runtime_error(msg.str());
  }

  void MockPCA9685::Register(HardwareProviderRegistrar& registrar) {
    registrar.RegisterPWMChannelProvider( this->name, this );
  }
}
