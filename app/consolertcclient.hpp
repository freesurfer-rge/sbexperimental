#pragma once

#include "railtrafficcontrolclient.hpp"

namespace Signalbox {
  class ConsoleRTCClient : public RailTrafficControlClient {
  public:
    ConsoleRTCClient() :
      host(),
      port() {}

    virtual void SendTrackCircuitNotification( const ItemId trackCircuitId,
                                               const bool occupied ) override;

    std::string host;
    uint16_t port;
  };
}
