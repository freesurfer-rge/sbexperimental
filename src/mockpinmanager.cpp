#include <sstream>
#include <stdexcept>

#include "mockpinmanager.hpp"

namespace Signalbox {

  MockDigitalOutputPin* MockPinManager::FetchMockDigitalOutputPin(const std::string pinId) const {
    return this->getOutputPin(pinId);
  }

  MockDigitalInputPin* MockPinManager::FetchMockDigitalInputPin(const std::string pinId) const {
    std::stringstream msg;
    msg << __FUNCTION__
	<< ": Not implemented"
	<< " (" << pinId << ")";
    throw std::runtime_error(msg.str());
  }

  std::string MockPinManager::parsePinId( const std::string idString ) const {
    return idString;
  }
}
