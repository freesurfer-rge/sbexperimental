#pragma once

#include "controlleditem.hpp"

#include "turnoutstate.hpp"

namespace Signalbox {
  class TurnoutMotor : public ControlledItem {
  public:
    virtual void SetState(const TurnoutState desired) = 0;

    TurnoutState getState() const;

    virtual std::string getTypeString() const override;
  protected:
    TurnoutState state;

    TurnoutMotor(const ItemId turnoutId) :
      ControlledItem(turnoutId),
      state(TurnoutState::Straight) {}
  };
}
