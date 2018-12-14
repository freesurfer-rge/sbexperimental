#pragma once

#include <map>
#include <memory>

#include "controlleditemfactoryselector.hpp"
#include "pinmanager.hpp"
#include "signalheadfactory.hpp"

namespace Signalbox {
  class ControlledItemManager : public ControlledItemFactorySelector {
  public:
    ControlledItemManager( PinManager* pm ) :
      pinManager(pm),
      signalHeadFactory(pm),
      items() {}
    
    virtual ControlledItemFactory* GetSignalHeadFactory() override;

    virtual ControlledItemFactory* GetTurnoutMotorFactory() override;

    virtual ControlledItemFactory* GetTrackCircuitMonitorFactory() override;

    std::unique_ptr<ControlledItem> CreateItem(const ControlledItemData* data);

    size_t PopulateItems(const std::vector< std::unique_ptr<ControlledItemData> >& items);
    
    // Remove copy constructor and operator=
    ControlledItemManager(ControlledItemManager&) = delete;
    ControlledItemManager& operator=(ControlledItemManager&) = delete;
  private:
    PinManager* pinManager;

    SignalHeadFactory signalHeadFactory;

    std::map<ItemId,std::unique_ptr<ControlledItem>> items;   
  };
}
