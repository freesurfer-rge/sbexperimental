#pragma once

#include "controlleditemfetcher.hpp"

namespace Signalbox {
  class ControlledItemDriver {
  public:
    virtual ~ControlledItemDriver() {}
    
    virtual void Run(ControlledItemFetcher* f) = 0;
  };
}
