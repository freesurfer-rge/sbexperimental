#include "mockpwmchannel.hpp"

namespace Signalbox {
  void MockPWMChannel::Set(const unsigned int value ) {
    this->state = value;
  }

  unsigned int MockPWMChannel::Get() const {
    return this->state;
  }
}
