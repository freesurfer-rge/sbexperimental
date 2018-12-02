#include "mockdigitaloutputpin.hpp"

namespace Signalbox {
  void MockDigitalOutputPin::Set(const bool level) {
    this->state = level;
  }

  bool MockDigitalOutputPin::Get() const {
    return this->state;
  }
}
