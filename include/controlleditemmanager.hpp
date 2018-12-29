#pragma once

#include <map>
#include <memory>

#include "controlleditemfactoryselector.hpp"
#include "controlleditemfetcher.hpp"
#include "pinmanager.hpp"
#include "pinmanagerfactory.hpp"
#include "signalheadfactory.hpp"

namespace Signalbox {
  class ControlledItemManager : public ControlledItemFactorySelector, public ControlledItemFetcher {
  public:
    ControlledItemManager( PinManagerFactory* pm ) :
      pinManager(pm->Create()),
      signalHeadFactory(this->pinManager.get()),
      items() {}
    
    virtual ControlledItemFactory* GetSignalHeadFactory() override;

    virtual ControlledItemFactory* GetTurnoutMotorFactory() override;

    virtual ControlledItemFactory* GetTrackCircuitMonitorFactory() override;

    std::unique_ptr<ControlledItem> CreateItem(const ControlledItemData* data);

    size_t PopulateItems(const std::vector< std::unique_ptr<ControlledItemData> >& items);

    size_t ActivateItems();
    
    virtual ControlledItem* GetById(const ItemId id) override;

    virtual std::vector<ControlledItem*> GetAllItems() override;
    
    // Remove copy constructor and operator=
    ControlledItemManager(ControlledItemManager&) = delete;
    ControlledItemManager& operator=(ControlledItemManager&) = delete;
  private:
    std::unique_ptr<PinManager> pinManager;

    SignalHeadFactory signalHeadFactory;

    std::map<ItemId,std::unique_ptr<ControlledItem>> items;   
  };
}
