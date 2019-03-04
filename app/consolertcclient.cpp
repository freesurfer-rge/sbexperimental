#include <sstream>

#include "consolertcclient.hpp"

namespace Signalbox {
  void ConsoleRTCClient::SendTrackCircuitNotification( const ItemId trackCircuitId,
						       const bool occupied ) {
    std::cout << "Update from "
	      << trackCircuitId
	      << " : ";
    if( occupied ) {
      std::cout << "Occupied";
    } else {
      std::cout << "Vacant";
    }
    std::cout << ". Sending to "
	      << this->host << ":" << std::dec << this->port
	      << std::endl;
  }
}
