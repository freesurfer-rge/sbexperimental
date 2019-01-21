#include <stdexcept>

#include "configuration/utils.hpp"

#include "digitaloutputpindata.hpp"

namespace Signalbox {
  DigitalOutputPinData::DigitalOutputPinData( const xercesc::DOMElement* xmlElement ) :
    id(),
    control() {
    if( !Configuration::IsOutputPin(xmlElement) ) {
      throw std::runtime_error("DigitalOutputPinData given non-OutputPin XML fragment");
    }

    this->id = Configuration::GetIdAttribute(xmlElement);
    this->control = Configuration::GetAttributeByName(xmlElement, "control");
  }
    
  std::string DigitalOutputPinData::getId() const {
    return this->id;
  }

  std::string DigitalOutputPinData::getControl() const {
    return this->control;
  }
}
