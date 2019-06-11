#include <sstream>
#include <stdexcept>

#include "mockpca9685.hpp"

namespace Signalbox {
  void MockPCA9685::Initialise( const std::map<std::string,std::string>& settings ) {
    std::stringstream msg;
    msg << __PRETTY_FUNCTION__
	<< " not implemented";
    throw std::runtime_error(msg.str());
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
