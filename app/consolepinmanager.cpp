#include <sstream>
#include <stdexcept>

#include "consolepinmanager.hpp"

namespace Signalbox {
  std::string ConsolePinManager::parsePinId( const std::string idString ) const {
    return idString;
  }

  void ConsolePinManager::setupInputPin( ConsoleDigitalInputPin* pin, const std::string pinId ) const {
    pin->id = pinId;
  }

  void ConsolePinManager::setupOutputPin( ConsoleDigitalOutputPin* pin, const std::string pinId ) const {
    pin->id = pinId;
  }
}
