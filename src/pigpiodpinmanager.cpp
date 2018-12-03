#include <sstream>
#include <stdexcept>

#include "pigpiodpinmanager.hpp"

namespace Signalbox {
  int PiGPIOdPinManager::ParseId(const std::string pinId) const {
    // Format is GPIOnn
    int pin = std::stoi(pinId.substr(4,2));

    return pin;
  }
  
  DigitalOutputPin* PiGPIOdPinManager::CreateDigitalOutputPin(const std::string pinId) {
    const int id = this->ParseId(pinId);
    
     if( this->outputPins.count(id) != 0 ) {
      std::stringstream msg;
      msg << "Pin '" << pinId << "' already exists";
      throw std::runtime_error(msg.str());
    }

     auto nxt = std::unique_ptr<PiGPIOdDigitalOutputPin>(new PiGPIOdDigitalOutputPin());

     this->outputPins[id] = std::move(nxt);

     return this->outputPins[id].get();
  }
}
