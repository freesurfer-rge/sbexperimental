#pragma once
#include "outputselector.hpp"

namespace Signalbox {
  class PiGPIOdOutputSelector : public OutputSelector {
  public:
    PiGPIOdOutputSelector() {
      this->AddSelector( std::string("pigpio"), this );
    }

    virtual std::unique_ptr<PinManager> CreatePinManager() override;
  };
}
