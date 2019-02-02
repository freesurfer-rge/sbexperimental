#include "mockrailtrafficcontrolclient.hpp"

#include <stdexcept>

namespace Signalbox {
  void MockRailTrafficControlClient::SendTrackCircuitNotification( const ItemId trackCircuitId,
								   const bool occupied ) {
    throw std::runtime_error("Not implemented");
  }
}
