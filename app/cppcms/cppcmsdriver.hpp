#pragma once

#include "controlleditemdriver.hpp"

namespace Signalbox {
  class CPPCMSDriver : public ControlledItemDriver {
  public:
    // Some sample commands:
    // curl http://loki:8080 -H "Content-Type: application/json" --data '{ "method":"setsignalhead", "params": [ "00:00:00:02", "Yellow", "Steady" ], "id" : 1}'
    // curl http://loki:8080 -H "Content-Type: application/json" --data '{ "method":"getsignalhead", "params": [ "00:00:00:02" ], "id" : 1}'
    virtual void Run(ControlledItemFetcher* f) override;
  };
}
