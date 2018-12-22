#pragma once

#include <memory>

#include "controlleditemdeclarations.hpp"
  
#include "pinmanager.hpp"

#include "controlleditemdata.hpp"
#include "controlleditem.hpp"

namespace Signalbox {
  
  class ControlledItemFactory {
  public:
    virtual ~ControlledItemFactory() {}
    
    virtual std::unique_ptr<ControlledItem> Manufacture(const ControlledItemData* cid) = 0;
  };
}
