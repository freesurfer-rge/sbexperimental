#include <sstream>
#include <stdexcept>

#include "consolepinmanager.hpp"

namespace Signalbox {
  std::string ConsolePinManager::parsePinId( const std::string idString ) const {
    return idString;
  }

  void ConsolePinManager::setupInputPin( ConsoleDigitalInputPin* pin, const DigitalInputPinData& data ) const {
    pin->id = data.id;
  }

  void ConsolePinManager::setupOutputPin( ConsoleDigitalOutputPin* pin, const std::string pinId ) const {
    pin->id = pinId;
  }
}
