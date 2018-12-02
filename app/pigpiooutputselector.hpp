#pragma once
#include "outputselector.hpp"

namespace Signalbox {
  class PiGPIOOutputSelector : public OutputSelector {
  public:
    PiGPIOOutputSelector() {
      this->AddSelector( std::string("pigpio"), this );
    }

    virtual std::unique_ptr<PinManager> CreatePinManager() override;
  };
}
