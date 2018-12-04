#pragma once

#include <string>

namespace Signalbox {
  class ControlledItemDataError {
  public:
    ControlledItemDataError() : message() {}
    
    std::string message;
  };
}
