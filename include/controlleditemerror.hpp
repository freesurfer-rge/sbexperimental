#pragma once

#include <string>

namespace Signalbox {
  class ControlledItemError {
  public:
    ControlledItemError() : message() {}
    
    std::string message;
  };
}
