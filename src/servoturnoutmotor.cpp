#include <sstream>
#include <stdexcept>

#include "servoturnoutmotor.hpp"

namespace Signalbox {
  void ServoTurnoutMotor::SetState(const TurnoutState desired) {
    if( desired == TurnoutState::Straight ) {
      this->servo->Set(pwmStraight);
      this->state = TurnoutState::Straight;
    } else if( desired == TurnoutState::Curved ) {
      this->servo->Set(pwmCurved);
      this->state = TurnoutState::Curved;
    } else {
      std::stringstream msg;
      msg << "Unsupported state: " << desired;
      throw std::runtime_error(msg.str());
    }
  }
}
