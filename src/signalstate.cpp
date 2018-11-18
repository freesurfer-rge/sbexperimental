#include "signalstate.hpp"

namespace Signalbox {
  std::ostream& operator<<( std::ostream& os, const SignalState s ) {
    
    switch( s ) {
    case SignalState::Inactive:
      os << "Inactive";
      break;

    case SignalState::Done:
      os << "Done";
      break;

    case SignalState::Red:
      os << "Red";
      break;

    case SignalState::DoubleYellow:
      os << "DoubleYellow";
      break;

    case SignalState::Yellow:
      os << "Yellow";
      break;

    case SignalState::Green:
      os << "Green";
      break;

    default:
      throw std::runtime_error("Unrecognised SignalState in operator<<");
    }
    
    return os;
  }
}
