#pragma once

#include <string>
#include <map>

namespace Signalbox {
  class DigitalInputPinData {
  public:
    DigitalInputPinData();
    
    std::string id;
    std::string sensor;
    std::map<std::string,std::string> settings;
  };
}
