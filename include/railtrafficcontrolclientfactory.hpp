#pragma once

#include <memory>

#include "railtrafficcontroldata.hpp"
#include "railtrafficcontrolclient.hpp"

namespace Signalbox {
  class RailTrafficControlClientFactory {
  public:
    virtual ~RailTrafficControlClientFactory() {}

    virtual std::unique_ptr<RailTrafficControlClient> Create(const RailTrafficControlData rtcData) = 0;
  };
}
