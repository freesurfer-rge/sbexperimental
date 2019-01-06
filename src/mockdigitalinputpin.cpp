#include "mockdigitalinputpin.hpp"

namespace Signalbox {
  bool MockDigitalInputPin::Get() const {
    return this->state;
  }

  void MockDigitalInputPin::Set(const bool level) {
    throw std::runtime_error("Not implemented");
  }
}
