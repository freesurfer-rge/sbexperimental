#include "turnoutmotor.hpp"

#include <sstream>
#include <stdexcept>

namespace Signalbox {  
  TurnoutState TurnoutMotor::getState() const {
    return this->state;
  }

  std::string TurnoutMotor::getTypeString() const {
    return std::string("turnoutmotor");
  }
}
