#pragma once

#include "railtrafficcontrolclient.hpp"

namespace Signalbox {
  class MockRailTrafficControlClient : public RailTrafficControlClient {
  public:
    MockRailTrafficControlClient() :
      RailTrafficControlClient(),
      host(),
      port(),
      lastItem(),
      lastOccupy() {}

    virtual void SendTrackCircuitNotification( const ItemId trackCircuitId,
					       const bool occupied ) override;

    std::string host;
    uint16_t port;
    ItemId lastItem;
    bool lastOccupy;
  };
}
