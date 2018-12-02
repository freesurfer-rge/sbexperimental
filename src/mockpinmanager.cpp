#include "mockpinmanager.hpp"

#include <sstream>
#include <stdexcept>

namespace Signalbox {
  DigitalOutputPin* MockPinManager::CreateDigitalOutputPin(const std::string pinId) {
    if( this->outputPins.count(pinId) != 0 ) {
      std::stringstream msg;
      msg << "Pin '" << pinId << "' already exists";
      throw std::runtime_error(msg.str());
    }
    
    auto nxt = std::unique_ptr<MockDigitalOutputPin>(new MockDigitalOutputPin());
    this->outputPins[pinId] = std::move(nxt);

    return this->outputPins[pinId].get();
  }
}
