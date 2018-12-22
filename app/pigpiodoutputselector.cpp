#include "pigpiodoutputselector.hpp"

namespace Signalbox {
  static PiGPIOdOutputSelector piGPIOd;

  PinManagerFactory* PiGPIOdOutputSelector::GetPinManagerFactory() {
    return &(this->pgdpmf);
  }
}
