#pragma once

#include "controlleditemdriver.hpp"

namespace Signalbox {
  class CPPCMSDriver : ControlledItemDriver {
  public:
    // Some sample commands:
    // curl http://loki:8080 -H "Content-Type: application/json" --data '{ "method":"setsignalhead", "params": [ 1, 5, 0 ], "id" : 1}'
    // curl http://loki:8080 -H "Content-Type: application/json" --data '{ "method":"getsignalhead", "params": [ 1 ], "id" : 1}'
    virtual void Run(ControlledItemFetcher* f) override;
  };
}
