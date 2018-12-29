#pragma once

#include <cppcms/service.h>
#include <cppcms/rpc_json.h>

#include "controlleditemfetcher.hpp"

namespace Signalbox {
  class ControlledItemService : public cppcms::rpc::json_rpc_server {
  public:
    ControlledItemService(cppcms::service& srv);

    void SetSignalHead( int id, int aspect, int flashing );

    void GetSignalHead( int id );

    ControlledItemFetcher* cif;
  };
}
