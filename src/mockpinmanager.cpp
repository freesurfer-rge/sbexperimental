#include "mockpinmanager.hpp"

namespace Signalbox {
  DigitalOutputPin* MockPinManager::CreateDigitalOutputPin(const std::string pinId) {
    throw std::runtime_error("CreateDigitalOutputPin(Mock) not implemented");
  }
}
