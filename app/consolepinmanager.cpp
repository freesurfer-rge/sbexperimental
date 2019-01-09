#include <sstream>
#include <stdexcept>

#include "consolepinmanager.hpp"

namespace Signalbox {
  DigitalOutputPin* ConsolePinManager::CreateDigitalOutputPin(const std::string pinId) {
    this->checkIfPinExists(pinId);
    
    auto nxt = std::unique_ptr<ConsoleDigitalOutputPin>(new ConsoleDigitalOutputPin());
    nxt->id = pinId;
    this->outputPins[pinId] = std::move(nxt);

    return this->outputPins[pinId].get();
  }

  DigitalInputPin* ConsolePinManager::CreateDigitalInputPin(const std::string pinId) {
    this->checkIfPinExists(pinId);

    auto nxt = std::unique_ptr<ConsoleDigitalInputPin>(new ConsoleDigitalInputPin());
    nxt->id = pinId;
    
    this->inputPins[pinId] = std::move(nxt);

    return this->inputPins[pinId].get();
  }
}
