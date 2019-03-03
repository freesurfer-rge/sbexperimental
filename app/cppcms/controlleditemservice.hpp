#pragma once

#include <cppcms/service.h>
#include <cppcms/rpc_json.h>

#include "itemid.hpp"
#include "signalaspect.hpp"
#include "signalflash.hpp"

#include "controlleditemfetcher.hpp"

namespace Signalbox {
  class ControlledItemService : public cppcms::rpc::json_rpc_server {
  public:
    ControlledItemService(cppcms::service& srv);

    void ListControlledItems();
    
    void SetSignalHead( ItemId id, SignalAspect aspect, SignalFlash flashing );
    void GetSignalHead( ItemId id );

    void GetTrackCircuitMonitor( ItemId id );

    ControlledItemFetcher* cif;

    // Protect pointer member
    ControlledItemService(const ControlledItemService&) = delete;
    ControlledItemService operator=(const ControlledItemService&) = delete;
  };
}
