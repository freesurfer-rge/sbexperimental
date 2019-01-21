#include <stdexcept>

#include "configuration/utils.hpp"

#include "outputpindata.hpp"

namespace Signalbox {
  OutputPinData::OutputPinData( const xercesc::DOMElement* xmlElement ) :
    id(),
    control() {
    if( !Configuration::IsOutputPin(xmlElement) ) {
      throw std::runtime_error("OutputPinData given non-OutputPin XML fragment");
    }

    this->id = Configuration::GetIdAttribute(xmlElement);
    this->control = Configuration::GetAttributeByName(xmlElement, "control");
  }
    
  std::string OutputPinData::getId() const {
    return this->id;
  }

  std::string OutputPinData::getControl() const {
    return this->control;
  }
}
