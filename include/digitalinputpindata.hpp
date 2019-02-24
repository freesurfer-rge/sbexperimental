#pragma once

#include <string>
#include <map>

#include <xercesc/dom/DOMElement.hpp>

namespace Signalbox {
  class DigitalInputPinData {
  public:
    DigitalInputPinData( const xercesc::DOMElement* xmlElement );

    std::string getId() const;

    std::string getSensor() const;

    bool hasSetting(const std::string name) const;

    std::string getSetting( const std::string name) const;

  private:
    std::string id;
    std::string sensor;
    std::map<std::string,std::string> settings;
  };
}
