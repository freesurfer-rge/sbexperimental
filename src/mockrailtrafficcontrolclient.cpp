#include "mockrailtrafficcontrolclient.hpp"

#include <stdexcept>

namespace Signalbox {
  void MockRailTrafficControlClient::SendTrackCircuitNotification( const ItemId trackCircuitId,
								   const bool occupied ) {
    this->lastItem = trackCircuitId;
    this->lastOccupy = occupied;
  }
}
