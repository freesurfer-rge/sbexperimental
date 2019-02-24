#pragma once

#include <string>

#include "controlleditemdata.hpp"
#include "digitalinputpindata.hpp"

namespace Signalbox {
  class TrackCircuitData : public ControlledItemData {
  public:
    TrackCircuitData() : ControlledItemData(),
			 inputPin() {}

    DigitalInputPinData inputPin;

    virtual std::vector<ControlledItemDataError> GetErrors() const override;

    virtual ControlledItemFactory* GetFactory(ControlledItemFactorySelector* factorySelector) const override;
  };
}
