#include <sstream>
#include <stdexcept>

#include "mockpinmanager.hpp"

namespace Signalbox {

  MockDigitalOutputPin* MockPinManager::FetchMockDigitalOutputPin(const std::string pinId) const {
    return this->getOutputPin(pinId);
  }

  MockDigitalInputPin* MockPinManager::FetchMockDigitalInputPin(const std::string pinId) const {
    return this->getInputPin(pinId);
  }

  std::string MockPinManager::parsePinId( const std::string idString ) const {
    return idString;
  }
  
  void MockPinManager::setupInputPin( MockDigitalInputPin* pin, const DigitalInputPinData& data ) const {
    pin->id = data.id;
    pin->createSettings = data.settings;
  }
}
