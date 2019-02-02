#pragma once

#include "itemid.hpp"

namespace Signalbox {
  class RailTrafficControlClient {
  public:
    virtual ~RailTrafficControlClient() {}
    
    virtual void SendTrackCircuitNotification( const ItemId trackCircuitId,
					       const bool occupied ) = 0;
  };
}
