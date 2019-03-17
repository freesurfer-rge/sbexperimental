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

    virtual void Activate() {};

    virtual void Deactivate() {};

    virtual std::string getTypeString() const = 0;
  private:
    ItemId id;
  };
}
