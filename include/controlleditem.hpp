#pragma once

#include <vector>

#include "itemid.hpp"

#include "controlleditemerror.hpp"

namespace Signalbox {
  class ControlledItem {
  public:
    ItemId id;

    virtual ~ControlledItem() {}

    virtual std::vector<ControlledItemError> GetErrors() const = 0;
  };
}
