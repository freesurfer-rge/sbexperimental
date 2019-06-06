#pragma once

#include <memory>

#include "pwmchannel.hpp"

#include "turnoutmotor.hpp"

namespace Signalbox {
  class ServoTurnoutMotor : public TurnoutMotor {
  public:
    virtual void SetState(const TurnoutState desired) override;

  private:
    unsigned int pwmStraight;
    unsigned int pwmCurved;
    std::weak_ptr<PWMChannel> servo;

    ServoTurnoutMotor(const ItemId turnoutId) :
      TurnoutMotor(turnoutId),
      pwmStraight(0),
      pwmCurved(0),
      servo() {}
  };
}
