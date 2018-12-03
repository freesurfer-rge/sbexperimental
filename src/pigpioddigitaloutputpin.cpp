#include <stdexcept>
#include <sstream>

#include <pigpiod_if2.h>

#include "pigpioddigitaloutputpin.hpp"

namespace Signalbox {
  PiGPIOdDigitalOutputPin::PiGPIOdDigitalOutputPin(const int pi, const int pin) :
    piId(pi),
    pinId(pin) {
    int err = set_mode(this->piId, this->pinId, PI_OUTPUT);
    if( err != 0 ) {
      std::stringstream msg;
      msg << "set_mode failed for Pi: "
	  << this->piId
	  << " pin: " << this->pinId
	  << " error: " << err;
      throw std::runtime_error(msg.str());
    }
  }
  
  void PiGPIOdDigitalOutputPin::Set(const bool level) {
    int res;
    if( level ) {
      res = gpio_write(this->piId, this->pinId, 1);
    } else {
      res = gpio_write(this->piId, this->pinId, 0);
    }
    if( res != 0 ) {
      std::stringstream msg;
      msg << "gpio_write failed for Pi: "
	  << this->piId
	  << " pin: " << this->pinId
	  << " error: " << res;
      throw std::runtime_error(msg.str());
    }
  }

  bool PiGPIOdDigitalOutputPin::Get() const {
    int res = gpio_read(this->piId, this->pinId);
    if( res == PI_BAD_GPIO ) {
      std::stringstream msg;
      msg << "gpio_read failed for Pi: "
	  << this->piId
	  << " pin: " << this->pinId
	  << " error: " << res;
      throw std::runtime_error(msg.str());
    }

    return 1==res;
  }
}
