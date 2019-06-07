#pragma once

#include "devicerequestdata.hpp"
#include "controlleditemdata.hpp"

namespace Signalbox {
  class ServoTurnoutMotorData : public ControlledItemData {
  public:
    ServoTurnoutMotorData() : ControlledItemData(),
			      straight(),
			      curved(),
			      pwmChannelRequest() {}

    unsigned int straight;
    unsigned int curved;
    DeviceRequestData pwmChannelRequest;

    virtual std::vector<ControlledItemDataError> GetErrors() const override;

    virtual ControlledItemFactory* GetFactory(ControlledItemFactorySelector* factorySelector) const override;
  };
}
