#pragma once

#include <string>
#include <map>

namespace Signalbox {
  class I2CDeviceData {
  public:
    I2CDeviceData() :
      kind(),
      bus(32768),
      address(32768),
      name(),
      settings() {}
    
    std::string kind;
    unsigned int bus;
    unsigned int address;
    std::string name;
    std::map<std::string,std::string> settings;
  };
}
