#include <sstream>
#include <stdexcept>

#include "consolepinmanager.hpp"

namespace Signalbox {
  PWMChannel* ConsolePinManager::CreatePWMChannel(const DeviceRequestData& data) {
    if( this->pwmChannels.count(this->getKey(data)) != 0 ) {
      std::stringstream msg;
      msg << "PWMChannel '" << this->getKey(data) << "' already exists";
      throw std::runtime_error(msg.str());
    }
    auto nxt = std::unique_ptr<ConsolePWMChannel>(new ConsolePWMChannel);
    nxt->controller = data.controller;
    nxt->controllerData = data.controllerData;

    this->pwmChannels[this->getKey(data)] = std::move(nxt);

    return this->pwmChannels[this->getKey(data)].get();
  }
  
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
