#include <sstream>
#include <stdexcept>

#include "mockpinmanager.hpp"

namespace Signalbox {
  DigitalOutputPin* MockPinManager::CreateDigitalOutputPin(const std::string pinId) {
    this->checkIfPinExists(pinId);
    
    auto nxt = std::unique_ptr<MockDigitalOutputPin>(new MockDigitalOutputPin());
    this->outputPins[pinId] = std::move(nxt);

    return this->outputPins[pinId].get();
  }

  DigitalInputPin* MockPinManager::CreateDigitalInputPin(const std::string pinId) {
    this->checkIfPinExists(pinId);

    auto nxt = std::unique_ptr<MockDigitalInputPin>(new MockDigitalInputPin());

    this->inputPins[pinId] = std::move(nxt);

    return this->inputPins[pinId].get();
  }

  MockDigitalOutputPin* MockPinManager::FetchMockDigitalOutputPin(const std::string pinId) const {
    return this->outputPins.at(pinId).get();
  }

  MockDigitalInputPin* MockPinManager::FetchMockDigitalInputPin(const std::string pinId) const {
    throw std::runtime_error("Not yet implemented");
  }
}
