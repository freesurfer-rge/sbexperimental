#include <sstream>
#include <stdexcept>

#include "consolepinmanager.hpp"

namespace Signalbox {
  DigitalOutputPin* ConsolePinManager::CreateDigitalOutputPin(const std::string pinId) {
    if( this->outputPins.count(pinId) != 0 ) {
      std::stringstream msg;
      msg << "Pin '" << pinId << "' already exists";
      throw std::runtime_error(msg.str());
    }
    
    auto nxt = std::unique_ptr<ConsoleDigitalOutputPin>(new ConsoleDigitalOutputPin());
    nxt->id = pinId;
    this->outputPins[pinId] = std::move(nxt);

    return this->outputPins[pinId].get();
  }
}
