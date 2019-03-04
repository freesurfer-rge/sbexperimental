#pragma once

#include <memory>

#include "mockpinmanagerfactory.hpp"
#include "mockrailtrafficcontrolclient.hpp"

struct MockPinManagerFactoryFixture {
  Signalbox::MockPinManagerFactory mpmf;
  std::shared_ptr<Signalbox::MockRailTrafficControlClient> rtcClient;

  MockPinManagerFactoryFixture() :
    mpmf(),
    rtcClient(new Signalbox::MockRailTrafficControlClient()) {
    rtcClient->host = "default.host";
    rtcClient->port = 1022;
  }
};
