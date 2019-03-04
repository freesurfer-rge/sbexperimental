#pragma once

#include "pinmanager.hpp"
#include "railtrafficcontrolclient.hpp"

#include "controlleditemfactory.hpp"

namespace Signalbox {
  class TrackCircuitMonitorFactory : public ControlledItemFactory {
  public:
    TrackCircuitMonitorFactory(PinManager* pm, RailTrafficControlClient* rtc) :
      pinManager(pm),
      rtcClient(rtc) {}

    virtual std::unique_ptr<ControlledItem> Manufacture(const ControlledItemData* cid) override;

    // Remove copy constructor and operator=
    TrackCircuitMonitorFactory(TrackCircuitMonitorFactory&) = delete;
    TrackCircuitMonitorFactory& operator=(TrackCircuitMonitorFactory&) = delete;
  private:
    PinManager* pinManager;
    RailTrafficControlClient* rtcClient;
  };
}
