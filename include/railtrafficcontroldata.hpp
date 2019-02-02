#pragma once

#include <string>

namespace Signalbox {
  class RailTrafficControlData {
  public:
    RailTrafficControlData() :
      host("NotSet"),
      port(0) {}
    
    std::string host;

    uint16_t port;
  };
}
