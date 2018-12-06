#include <sstream>
#include <stdexcept>

#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "signalheadfactory.hpp"

namespace Signalbox {
  std::unique_ptr<ControlledItem> SignalHeadFactory::Manufacture(const ControlledItemData* cid) {
    auto sd = dynamic_cast<const SignalHeadData*>(cid);
    if( sd == NULL ) {
      std::stringstream msg;
      msg << "Failed to cast ControlledItemData to SignalHeadData";
      throw std::runtime_error(msg.str());
    }
    
    std::unique_ptr<SignalHead> res;
    res.reset( new SignalHead(sd->id) );

    // Add pins
    for( auto it=sd->pinData.begin(); it!=sd->pinData.end(); ++it ) {
      auto lamp = (*it).first;
      auto pinId = (*it).second;
      res->pins[lamp] = SignalHead::PinSwitch(false,
					      this->pinManager->CreateDigitalOutputPin(pinId));
      res->pins[lamp].pin->TurnOff();
    }
    // Turn red on
    auto p = &res->pins[SignalHeadPins::Red];
    p->isActive = true;
    p->pin->TurnOn();

    return std::unique_ptr<ControlledItem>(res.release());
  }
}
