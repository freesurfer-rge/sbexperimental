#pragma once

#include "railtrafficcontrolclientfactory.hpp"

#include "consolertcclient.hpp"

namespace Signalbox {
  class ConsoleRTCClientFactory : public RailTrafficControlClientFactory {
  public:
    virtual std::shared_ptr<RailTrafficControlClient> Create(const RailTrafficControlData rtcData) override {
      auto res = std::unique_ptr<ConsoleRTCClient>(new ConsoleRTCClient() );

      res->host = rtcData.host;
      res->port = rtcData.port;

      return res;
    }

  };
}
