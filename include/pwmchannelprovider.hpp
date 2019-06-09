#pragma once

#include <string>
#include <map>

#include "pwmchannel.hpp"

namespace Signalbox {
  class PWMChannelProvider {
  public:
    virtual ~PWMChannelProvider() {}

    virtual PWMChannel* GetPWMChannel( const std::string channelId,
				       const std::map<std::string,std::string> settings ) = 0;
  };
}
