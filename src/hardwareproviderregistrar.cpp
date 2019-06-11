#include <sstream>
#include <stdexcept>

#include "hardwareproviderregistrar.hpp"

namespace Signalbox {
  void HardwareProviderRegistrar::RegisterPWMChannelProvider( const std::string providerName,
							      PWMChannelProvider* provider ) {
    std::stringstream msg;
    msg << __FUNCTION__
	<< " unable to register "
	<< providerName
	<< " due to lack of implementation"
	<< std::endl;
    throw std::runtime_error(msg.str());
  }

  PWMChannelProvider* HardwareProviderRegistrar::GetPWMChannelProvider( const std::string providerName ) const {
     std::stringstream msg;
     msg << __FUNCTION__
	<< " unable to get PWMChannel from "
	<< providerName
	<< " due to lack of implementation"
	<< std::endl;
    throw std::runtime_error(msg.str());
  }
}
