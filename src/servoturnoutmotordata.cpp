#include "servoturnoutmotordata.hpp"

namespace Signalbox {
  std::vector<ControlledItemDataError> ServoTurnoutMotorData::GetErrors() const {
    std::vector<ControlledItemDataError> result;

    if( this->id == ItemId(0) ) {
      ControlledItemDataError e;
      e.message = "Invalid id";
      result.push_back(e);
    }

    return result;
  }

  ControlledItemFactory* ServoTurnoutMotorData::GetFactory(ControlledItemFactorySelector* factorySelector) const {
    return factorySelector->GetServoTurnoutMotorFactory();
  }
}
