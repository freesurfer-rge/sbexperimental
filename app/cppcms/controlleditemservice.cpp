#include <sstream>

#include "iteminfo.hpp"
#include "iteminfojson.hpp"
#include "trackcircuitmonitorjson.hpp"
#include "signalheadjson.hpp"
#include "signalaspectjson.hpp"
#include "signalflashjson.hpp"
#include "turnoutstatejson.hpp"
#include "turnoutmotorjson.hpp"
#include "itemidjson.hpp"

#include "signalhead.hpp"
#include "trackcircuitmonitor.hpp"
#include "turnoutmotor.hpp"

#include "controlleditemservice.hpp"

namespace Signalbox {
  ControlledItemService::ControlledItemService(cppcms::service& srv)
    : cppcms::rpc::json_rpc_server(srv),
      cif(NULL) {
    // Item methods
    bind("listitems",
	 cppcms::rpc::json_method(&ControlledItemService::ListControlledItems, this),
	 method_role);
    
    // SignalHead methods
    bind("setsignalhead",
	 cppcms::rpc::json_method(&ControlledItemService::SetSignalHead, this),
	 method_role);
    bind("getsignalhead",
	 cppcms::rpc::json_method(&ControlledItemService::GetSignalHead, this),
	 method_role);
    
    // TrackCircuitMonitor methods
    bind("gettrackcircuitmonitor",
	 cppcms::rpc::json_method(&ControlledItemService::GetTrackCircuitMonitor, this),
	 method_role);

    // TurnoutMotor
    bind("setturnoutmotor",
	 cppcms::rpc::json_method(&ControlledItemService::SetTurnoutMotor, this),
	 method_role);
    bind("getturnoutmotor",
	 cppcms::rpc::json_method(&ControlledItemService::GetTurnoutMotor, this),
	 method_role);
  }

  void ControlledItemService::ListControlledItems() {
    std::cout << __FUNCTION__ << ": Starting" << std::endl;
    auto items = this->cif->GetAllItems();

    std::vector<ItemInfo> result;
    for( auto it=items.begin(); it!=items.end(); ++it ) {
      ItemInfo nxt;
      nxt.id = (*it)->getId();
      nxt.type = (*it)->getTypeString();
      result.push_back(nxt);
    }
    std::cout << __FUNCTION__ << ": Result constructed" << std::endl;
    return_result(result);
  }

  void ControlledItemService::SetSignalHead( ItemId id, SignalAspect aspect, SignalFlash flashing ) {
    auto ci = this->cif->GetById(id);
    if( ci == NULL ) {
      return_error("No such item");
    }
    auto sh = dynamic_cast<SignalHead*>(ci);
    if( sh == NULL ) {
      return_error("Item is not a SignalHead");
    }
    
    std::cout << __PRETTY_FUNCTION__
	      << ": Setting " << id
	      << " to " << aspect
	      << " and " << flashing
	      << std::endl;
    
    try {
      sh->SetState(aspect, flashing);
      return_result(*sh);
    }
    catch( std::exception& e ) {
      std::cerr << "Caught: " << e.what() << std::endl;
      std::stringstream msg;
      msg << "An error occurred: "
	  << e.what();
      return_error(msg.str());
    }
  }
  
  void ControlledItemService::GetSignalHead( ItemId id ) {
    std::cout << __PRETTY_FUNCTION__ << ": Starting" << std::endl;
    
    auto ci = this->cif->GetById(id);
    if( ci == NULL ) {
      return_error("No such item");
    }
    auto sh = dynamic_cast<SignalHead*>(ci);
    if( sh == NULL ) {
      return_error("Item is not a SignalHead");
    }
    
    return_result(*sh);
  }

  void ControlledItemService::GetTrackCircuitMonitor( ItemId id ) {
    std::cout << __PRETTY_FUNCTION__ << ": Starting" << std::endl;
    
    auto ci = this->cif->GetById(id);
    if( ci == NULL ) {
      return_error("No such item");
    }
    auto tcm = dynamic_cast<TrackCircuitMonitor*>(ci);
    if( tcm == nullptr ) {
      return_error("Item is not a TrackCircuitMonitor");
    }

    return_result(*tcm);
  }

  void ControlledItemService::SetTurnoutMotor( ItemId id, TurnoutState state ) {
    auto ci = this->cif->GetById(id);
    if( ci == NULL ) {
      return_error("No such item");
    }
    auto tm = dynamic_cast<TurnoutMotor*>(ci);
    if( tm == NULL ) {
      return_error("Item is not a TurnoutMotor");
    }
    
    std::cout << __PRETTY_FUNCTION__
	      << ": Setting " << id
	      << " to " << state
	      << std::endl;
    
    try {
      tm->SetState(state);
      return_result(*tm);
    }
    catch( std::exception& e ) {
      std::cerr << "Caught: " << e.what() << std::endl;
      std::stringstream msg;
      msg << "An error occurred: "
	  << e.what();
      return_error(msg.str());
    }
  }

  void ControlledItemService::GetTurnoutMotor( ItemId id ) {
    std::cout << __PRETTY_FUNCTION__ << ": Starting" << std::endl;
    
    auto ci = this->cif->GetById(id);
    if( ci == NULL ) {
      return_error("No such item");
    }
    auto sh = dynamic_cast<TurnoutMotor*>(ci);
    if( sh == NULL ) {
      return_error("Item is not a TurnoutMotor");
    }
    
    return_result(*sh);
  }
}

