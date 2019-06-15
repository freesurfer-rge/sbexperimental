#include <stdexcept>
#include <pigpiod_if2.h>

#include "pigpiodchecker.hpp"

#include "pca9685pwmchannel.hpp"

namespace Signalbox {
  void PCA9685PWMChannel::Set(const unsigned int value) {
    if( value >= 4096 ) {
      throw std::out_of_range("Must set value < 4096");
    }
    PIGPIOD_SAFE_CALL( i2c_write_word_data(this->piId, this->deviceHandle,
					   this->stopRegister, value) );
  }

  unsigned int PCA9685PWMChannel::Get() const {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
}
