#include <iostream>
#include <fstream>
#include <string>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/rpc_json.h>

#include "signalhead.hpp"

#include "cppcmsloop.hpp"

namespace Signalbox {
  class SignalHeadService : public cppcms::rpc::json_rpc_server {
  public:
    SignalHeadService(cppcms::service& srv)
      : cppcms::rpc::json_rpc_server(srv) {
      bind("set", cppcms::rpc::json_method(&SignalHeadService::set, this), method_role);
    }

    void set( int id, int aspect, int flashing ) {
      ItemId myId(id);

      auto ci = this->cim->GetById(myId);
      if( ci == NULL ) {
	return_error("No such item");
      }
      auto sh = dynamic_cast<SignalHead*>(ci);
      if( sh == NULL ) {
	return_error("Item is not a SignalHead");
      }

      auto a = static_cast<SignalAspect>(aspect);
      auto f = static_cast<SignalFlash>(flashing);
      
      sh->SetState(a, f);
      return_result("State set");
    }
    
    ControlledItemManager* cim;
  };
  
  void CppCMSLoop( ControlledItemManager* cim ) {
    std::string cppcmsConfigFile = "config.js";
    cppcms::json::value config;
    {
      std::ifstream cf(cppcmsConfigFile);

      cf >> config;
    }
    cppcms::service srv(config);
  }
}
