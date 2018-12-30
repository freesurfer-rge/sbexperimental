#pragma once
#include "driverselector.hpp"

namespace Signalbox {
  class ConsoleDriverSelector : public DriverSelector {
  public:
    ConsoleDriverSelector() {
      this->AddSelector( std::string("console"), this );
    }

    virtual ControlledItemDriver* GetDriver() override;
  };
}
