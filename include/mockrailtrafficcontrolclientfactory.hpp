#pragma once

#include "railtrafficcontrolclientfactory.hpp"

namespace Signalbox {
  class MockRailTrafficControlClientFactory : RailTrafficControlClientFactory {
  public:
    virtual std::shared_ptr<RailTrafficControlClient> Create(const RailTrafficControlData rtcData) override {
      auto mock = std::shared_ptr<MockRailTrafficControlClient>(new MockRailTrafficControlClient() );

      mock->host = rtcData.host;
      mock->port = rtcData.port;

      return mock;
    }
  };
}
