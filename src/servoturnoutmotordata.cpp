#include "servoturnoutmotordata.hpp"

namespace Signalbox {
  std::vector<ControlledItemDataError> ServoTurnoutMotorData::GetErrors() const {
    return std::vector<ControlledItemDataError>();
  }

  ControlledItemFactory* ServoTurnoutMotorData::GetFactory(ControlledItemFactorySelector* factorySelector) const {
    return factorySelector->GetServoTurnoutMotorFactory();
  }
}
