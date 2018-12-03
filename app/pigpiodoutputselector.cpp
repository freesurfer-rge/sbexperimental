#include "pigpiodpinmanager.hpp"

#include "pigpiodoutputselector.hpp"

namespace Signalbox {
  static PiGPIOdOutputSelector piGPIOd;

  std::unique_ptr<PinManager> PiGPIOdOutputSelector::CreatePinManager() {
    return std::unique_ptr<PinManager>(new PiGPIOdPinManager() );
  }
}
