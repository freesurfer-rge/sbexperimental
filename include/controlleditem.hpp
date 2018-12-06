#pragma once

#include "itemid.hpp"

namespace Signalbox {
  class ControlledItem {
  public:
    ControlledItem(const ItemId sigId) :
      id(sigId) {}

    virtual ~ControlledItem() {}
    
    ItemId getId() const {
      return this->id;
    }
    
  private:
    ItemId id;
  };
}
