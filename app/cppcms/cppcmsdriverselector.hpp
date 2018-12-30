#pragma once
#include "driverselector.hpp"

namespace Signalbox {
  class CPPCMSDriverSelector : public DriverSelector {
  public:
    CPPCMSDriverSelector() {
      this->AddSelector( std::string("cppcms"), this );
    }

    virtual ControlledItemDriver* GetDriver() override;
  };
}
