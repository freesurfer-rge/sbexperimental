#pragma once

#include <vector>

#include "controlleditem.hpp"

namespace Signalbox {
  class ControlledItemFetcher {
  public:
    virtual ~ControlledItemFetcher() {}
    
    virtual ControlledItem* GetById(const ItemId id) = 0;

    virtual std::vector<ControlledItem*> GetAllItems() = 0;
  };
}
