#pragma once

#include <string>

#include "controlleditemdata.hpp"
#include "digitalinputpindata.hpp"

namespace Signalbox {
  class TrackCircuitMonitorData : public ControlledItemData {
  public:
    TrackCircuitMonitorData() : ControlledItemData(),
				inputPin() {}

    DigitalInputPinData inputPin;

    virtual std::vector<ControlledItemDataError> GetErrors() const override;

    virtual ControlledItemFactory* GetFactory(ControlledItemFactorySelector* factorySelector) const override;
  };
}
