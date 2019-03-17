#pragma once

#include <map>
#include <memory>

#include "controlleditemfactoryselector.hpp"
#include "controlleditemfetcher.hpp"
#include "pinmanager.hpp"
#include "pinmanagerfactory.hpp"
#include "signalheadfactory.hpp"
#include "trackcircuitmonitorfactory.hpp"

#include "railtrafficcontrolclient.hpp"

namespace Signalbox {
  class ControlledItemManager : public ControlledItemFactorySelector, public ControlledItemFetcher {
  public:
    ControlledItemManager( PinManagerFactory* pm, std::shared_ptr<RailTrafficControlClient> rtc ) :
      pinManager(pm->Create()),
      rtcClient(rtc),
      signalHeadFactory(this->pinManager.get()),
      trackCircuitMonitorFactory(this->pinManager.get(), this->rtcClient.get()),
      items() {}

    ~ControlledItemManager() {
      for( auto it=this->items.begin(); it!=this->items.end(); it++ ) {
	(*it).second->Deactivate();
      }
    }
    
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
    
    std::shared_ptr<RailTrafficControlClient> rtcClient;

    SignalHeadFactory signalHeadFactory;
    TrackCircuitMonitorFactory trackCircuitMonitorFactory;

    std::map<ItemId,std::unique_ptr<ControlledItem>> items;   
  };
}
