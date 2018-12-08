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
      signalHeadFactory(pm) {}
    
    virtual ControlledItemFactory* GetSignalHeadFactory() override;

    virtual ControlledItemFactory* GetTurnoutMotorFactory() override;

    virtual ControlledItemFactory* GetTrackCircuitMonitorFactory() override;

    std::unique_ptr<ControlledItem> CreateItem(const ControlledItemData* data);

    // Remove copy constructor and operator=
    ControlledItemManager(ControlledItemManager&) = delete;
    ControlledItemManager& operator=(ControlledItemManager&) = delete;
  private:
    PinManager* pinManager;

    SignalHeadFactory signalHeadFactory;
    
  };
}
