#pragma once

#include "hardwareproviderregistrar.hpp"

namespace Signalbox {
  class HardwareProvider {
  public:
    virtual ~HardwareProvider() {}
    
    virtual void Register(HardwareProviderRegistrar& registrar) = 0;
  };
}
