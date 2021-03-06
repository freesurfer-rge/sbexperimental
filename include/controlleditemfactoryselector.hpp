#pragma once

#include "controlleditemdeclarations.hpp"

#include "controlleditemfactory.hpp"

namespace Signalbox {
  class ControlledItemFactorySelector {
  public:
    virtual ~ControlledItemFactorySelector() {}
    
    virtual ControlledItemFactory* GetSignalHeadFactory() = 0;

    virtual ControlledItemFactory* GetServoTurnoutMotorFactory() = 0;

    virtual ControlledItemFactory* GetTrackCircuitMonitorFactory() = 0;
  };
}
