#include <stdexcept>

#include "configuration/utils.hpp"

#include "digitalinputpindata.hpp"

namespace Signalbox {
  DigitalInputPinData::DigitalInputPinData( const xercesc::DOMElement* xmlElement ) :
    id(),
    sensor(),
    settings() {
    
    if( !Configuration::IsInputPin(xmlElement) ) {
      throw std::runtime_error("DigitalInputPinData given non-InputPin XML fragment");
    }

    this->id = Configuration::GetIdAttribute(xmlElement);
    this->sensor = Configuration::GetAttributeByName(xmlElement, "sensor");
  }

  std::string DigitalInputPinData::getId() const {
    return this->id;
  }

  std::string DigitalInputPinData::getSensor() const {
    return this->sensor;
  }

  bool DigitalInputPinData::hasSetting(const std::string name) const {
    return this->settings.count(name) == 1;
  }

  std::string DigitalInputPinData::getSetting(const std::string name) const {
    return this->settings.at(name);
  }
}
