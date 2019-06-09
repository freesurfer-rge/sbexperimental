#pragma once

#include "pinmanager.hpp"

#include "controlleditemfactory.hpp"

namespace Signalbox {
  class ServoTurnoutMotorFactory : public ControlledItemFactory {
  public:
    ServoTurnoutMotorFactory(PinManager* pm) :
      pinManager(pm) {}
    
    virtual std::unique_ptr<ControlledItem> Manufacture(const ControlledItemData* cid) override;

    // Remove copy constructor and operator=
    ServoTurnoutMotorFactory(ServoTurnoutMotorFactory&) = delete;
    ServoTurnoutMotorFactory& operator=(ServoTurnoutMotorFactory&) = delete;
  private:
    PinManager* pinManager;
  };
}
