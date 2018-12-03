#include <sstream>
#include <stdexcept>

#include "pigpiodpinmanager.hpp"

namespace Signalbox {
  int PiGPIOdPinManager::ParseId(const std::string pinId) const {
    // Format is GPIOnn
    int pin = std::stoi(pinId.substr(4,2));

    return pin;
  }
  
  DigitalOutputPin* PiGPIOdPinManager::CreateDigitalOutputPin(const std::string pinId) {
    std::stringstream msg;
    msg << __PRETTY_FUNCTION__ << ": Not implemented";
    throw std::runtime_error(msg.str());
  }
}
