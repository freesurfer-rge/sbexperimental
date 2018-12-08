#pragma once

#include <memory>

namespace Signalbox {
  class ControlledItem;
  class ControlledItemData;
  class ControlledItemFactory;
  class ControlledItemFactorySelector;
}
  
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
