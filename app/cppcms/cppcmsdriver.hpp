#pragma once

#include "controlleditemdriver.hpp"

namespace Signalbox {
  class CPPCMSDriver : public ControlledItemDriver {
  public:
    // Some sample commands:

    // List everything
    // curl http://loki:8080/rpc -H "Content-Type: application/json" --data '{ "method":"listitems", "params":[], "id":1 }'

    // SignalHeads
    // curl http://loki:8080/rpc -H "Content-Type: application/json" --data '{ "method":"setsignalhead", "params": [ "00:00:00:02", "Yellow", "Steady" ], "id" : 1}'
    // curl http://loki:8080/rpc -H "Content-Type: application/json" --data '{ "method":"getsignalhead", "params": [ "00:00:00:02" ], "id" : 1}'

    // TrackCircuitMonitors
    // curl http://loki:8080/rpc -H "Content-Type: application/json" --data '{ "method":"gettrackcircuitmonitor", "params" : [ "00:00:00:aa" ], "id" : 1}'

    // TurnoutMotors
    // curl http://loki:8080/rpc -H "Content-Type: application/json" --data '{ "method":"getturnoutmotor", "params" : [ "00:fe:1a:af" ], "id" : 1}'
    // curl http://loki:8080/rpc -H "Content-Type: application/json" --data '{ "method":"setturnoutmotor", "params" : [ "00:fe:1a:af", "Curved" ], "id" : 1}'

    virtual void Run(ControlledItemFetcher* f) override;
  };
}
