#pragma once

#include "railtrafficcontrolclient.hpp"

namespace Signalbox {
  class MockRailTrafficControlClient : public RailTrafficControlClient {
  public:
    MockRailTrafficControlClient() :
      RailTrafficControlClient(),
      lastItem(),
      lastOccupy() {}

    virtual void SendTrackCircuitNotification( const ItemId trackCircuitId,
					       const bool occupied ) override;

    ItemId lastItem;
    bool lastOccupy;
  };
}
