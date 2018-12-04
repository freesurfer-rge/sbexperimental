#pragma once

#include <vector>

#include "itemid.hpp"

#include "controlleditemdataerror.hpp"

namespace Signalbox {
  class ControlledItemData {
  public:
    ControlledItemData() : id(0) {}
    
    ItemId id;

    virtual ~ControlledItemData() {}

    virtual std::vector<ControlledItemDataError> GetErrors() const = 0;
  };
}
