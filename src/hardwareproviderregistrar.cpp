#include <sstream>
#include <stdexcept>

#include "hardwareproviderregistrar.hpp"

namespace Signalbox {
  void HardwareProviderRegistrar::RegisterPWMChannelProvider( const std::string providerName,
							      PWMChannelProvider* provider ) {
    if( this->pwmChannelProviders.count(providerName) != 0 ) {
      std::stringstream msg;
      msg << "PWMChannelProvider '"
	  << providerName
	  << "' already registered";
      throw std::out_of_range(msg.str());
    }
    this->pwmChannelProviders[providerName] = provider;
  }

  PWMChannelProvider* HardwareProviderRegistrar::GetPWMChannelProvider( const std::string providerName ) const {
    if( this->pwmChannelProviders.count(providerName) != 1 ) {
      std::stringstream msg;
      msg << "PWMChannelProvider '"
	  << providerName
	  << "' not found";
      throw std::out_of_range(msg.str());
    }
    return this->pwmChannelProviders.at(providerName);
  }
}
