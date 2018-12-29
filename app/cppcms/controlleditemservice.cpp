#include "signalheadjson.hpp"
#include "signalaspectjson.hpp"
#include "signalflashjson.hpp"
#include "itemidjson.hpp"

#include "signalhead.hpp"

#include "controlleditemservice.hpp"

namespace Signalbox {
  ControlledItemService::ControlledItemService(cppcms::service& srv)
    : cppcms::rpc::json_rpc_server(srv) {
    // SignalHead methods
    bind("setsignalhead",
	 cppcms::rpc::json_method(&ControlledItemService::SetSignalHead, this),
	 method_role);
    bind("getsignalhead",
	 cppcms::rpc::json_method(&ControlledItemService::GetSignalHead, this),
	 method_role);
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
    }
    catch( std::exception& e ) {
      std::cerr << "Caught: " << e.what() << std::endl;
      return_error("An error occurred");
    }
    return_result(*sh);
  }
  
  void ControlledItemService::GetSignalHead( ItemId id ) {
    // Sample call:
    // curl http://localhost:8080 -H "Content-Type: application/json" --data '{ "method":"getsignal", "params": [ 2 ], "id" : 1}'
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
}

