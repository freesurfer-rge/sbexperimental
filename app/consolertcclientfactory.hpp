#pragma once

#include "railtrafficcontrolclientfactory.hpp"

#include "consolertcclient.hpp"

namespace Signalbox {
  class ConsoleRTCClientFactory : public RailTrafficControlClientFactory {
  public:
    virtual std::unique_ptr<RailTrafficControlClient> Create(const RailTrafficControlData rtcData) override {
      auto res = std::unique_ptr<RailTrafficControlClient>(new ConsoleRTCClient() );

      auto mock = dynamic_cast<ConsoleRTCClient*>(res.get());
      mock->host = rtcData.host;
      mock->port = rtcData.port;

      return res;
    }

  };
}
