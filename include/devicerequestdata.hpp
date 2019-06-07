#pragma once

#include <string>

namespace Signalbox {
  class DeviceRequestData {
  public:
    std::string controller;
    std::string controllerData;
  };
}
