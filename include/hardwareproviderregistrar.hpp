#pragma once

#include <string>

#include "pwmchannelprovider.hpp"

namespace Signalbox {
  class HardwareProviderRegistrar {
  public:
    HardwareProviderRegistrar() :
      pwmChannelProviders() {}
    
    void RegisterPWMChannelProvider( const std::string providerName,
				     PWMChannelProvider* provider );

    PWMChannelProvider* GetPWMChannelProvider( const std::string providerName ) const;
    
  private:
    std::map<std::string,PWMChannelProvider*> pwmChannelProviders;
  };
}
