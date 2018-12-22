#pragma once

#include "pigpiodpinmanagerfactory.hpp"


#include "outputselector.hpp"

namespace Signalbox {
  class PiGPIOdOutputSelector : public OutputSelector {
  public:
    PiGPIOdOutputSelector() :
      pgdpmf() {
      this->AddSelector( std::string("pigpiod"), this );
    }

    virtual PinManagerFactory* GetPinManagerFactory() override;
  private:
    PiGPIOdPinManagerFactory pgdpmf;
  };
}
