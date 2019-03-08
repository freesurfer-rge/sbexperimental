#pragma once

#include <string>
#include <map>

namespace Signalbox {
  class DigitalInputPinData {
  public:
    DigitalInputPinData() :
      id(),
      sensor(),
      settings() {}
    
    std::string id;
    std::string sensor;
    std::map<std::string,std::string> settings;
  };
}
