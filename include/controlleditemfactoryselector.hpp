#pragma once

namespace Signalbox {
  class ControlledItem;
  class ControlledItemData;
  class ControlledItemFactory;
  class ControlledItemFactorySelector;
}

#include "controlleditemfactory.hpp"

namespace Signalbox {
  class ControlledItemFactorySelector {
  public:
    virtual ~ControlledItemFactorySelector() {}
    
    virtual ControlledItemFactory* GetSignalHeadFactory() = 0;

    virtual ControlledItemFactory* GetTurnoutMotorFactory() = 0;

    virtual ControlledItemFactory* GetTrackCircuitMonitorFactory() = 0;
  };
}
