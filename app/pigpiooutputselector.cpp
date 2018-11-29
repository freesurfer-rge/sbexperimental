#include "pigpiooutputselector.hpp"

namespace Signalbox {
  static PiGPIOOutputSelector piGPIO;

  std::unique_ptr<OutputPin> PiGPIOOutputSelector::GetSample() {
    throw std::runtime_error("Not implemented: pigpio");
  }
}
