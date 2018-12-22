#pragma once

#include <vector>

#include "controlleditemdeclarations.hpp"

#include "itemid.hpp"

#include "controlleditemdataerror.hpp"
#include "controlleditemfactoryselector.hpp"
#include "controlleditemfactory.hpp"

namespace Signalbox {
  class ControlledItemData {
  public:
    ControlledItemData() : id(0) {}
    
    ItemId id;

    virtual ~ControlledItemData() {}

    virtual std::vector<ControlledItemDataError> GetErrors() const = 0;

    virtual ControlledItemFactory* GetFactory(ControlledItemFactorySelector* factorySelector) const = 0;
  };
}
