#include "pigpiooutputselector.hpp"

namespace Signalbox {
  static PiGPIOOutputSelector piGPIO;

  std::unique_ptr<PinManager> PiGPIOOutputSelector::CreatePinManager() {
    throw std::runtime_error("Not implemented: pigpio");
  }
}
