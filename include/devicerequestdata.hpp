#pragma once

#include <string>

namespace Signalbox {
  class DeviceRequestData {
  public:
    DeviceRequestData() :
      controller("unset"),
      controllerData("unset") {}
    
    std::string controller;
    std::string controllerData;
  };
}
