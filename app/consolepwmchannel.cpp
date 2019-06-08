#include <iostream>

#include "consolepwmchannel.hpp"

namespace Signalbox {
  void ConsolePWMChannel::Set(const unsigned int value ) {
    std::cout << "Setting PWMChannel "
	      << "[" << this->controller
	      << ", " << this->controllerData
	      << "] to " << value << std::endl;
    this->state = value;
  }

  unsigned int ConsolePWMChannel::Get() const {
    return this->state;
  }
}
