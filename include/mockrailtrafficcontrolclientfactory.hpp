#pragma once

#include "railtrafficcontrolclientfactory.hpp"

namespace Signalbox {
  class MockRailTrafficControlClientFactory : RailTrafficControlClientFactory {
  public:
    virtual std::unique_ptr<RailTrafficControlClient> Create(const RailTrafficControlData rtcData) override {
      auto res = std::unique_ptr<RailTrafficControlClient>(new MockRailTrafficControlClient() );

      auto mock = dynamic_cast<MockRailTrafficControlClient*>(res.get());
      mock->host = rtcData.host;
      mock->port = rtcData.port;

      return res;
    }
  };
}
