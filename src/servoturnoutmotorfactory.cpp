#include <sstream>
#include <stdexcept>

#include "servoturnoutmotordata.hpp"
#include "servoturnoutmotor.hpp"

#include "servoturnoutmotorfactory.hpp"

namespace Signalbox {
  std::unique_ptr<ControlledItem> ServoTurnoutMotorFactory::Manufacture(const ControlledItemData* cid) {
    auto stmd = dynamic_cast<const ServoTurnoutMotorData*>(cid);
    if( stmd == NULL ) {
      std::stringstream msg;
      msg << "Failed to cast ControlledItemData to ServoTurnoutMotorData";
      throw std::runtime_error(msg.str());
    }

    std::unique_ptr<ServoTurnoutMotor> res;
    res.reset( new ServoTurnoutMotor(stmd->id) );

    res->pwmStraight = stmd->straight;
    res->pwmCurved = stmd->curved;
    res->servo = this->pinManager->CreatePWMChannel(stmd->pwmChannelRequest);

    res->servo->Set(res->pwmStraight);

    return std::unique_ptr<ControlledItem>(res.release());
  }
}
