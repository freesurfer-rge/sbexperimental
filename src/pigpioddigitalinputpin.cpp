#include <stdexcept>
#include <sstream>

#include <pigpiod_if2.h>

#include "pigpioddigitalinputpin.hpp"

namespace Signalbox {
  bool PiGPIOdDigitalInputPin::Get() const {
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
