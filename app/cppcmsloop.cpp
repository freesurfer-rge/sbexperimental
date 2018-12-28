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
      std::cout << __PRETTY_FUNCTION__ << ": Starting" << std::endl;
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

      std::cout << __PRETTY_FUNCTION__
		<< ": Setting " << myId
		<< " to " << a
		<< " and " << f
		<< std::endl;

      try {
	sh->SetState(a, f);
      }
      catch( std::exception& e ) {
	std::cerr << "Caught: " << e.what() << std::endl;
      }
      return_result("State set");
    }
    
    ControlledItemManager* cim;
  };

  class SignalHeadServiceFactory : public cppcms::application_specific_pool {
  public:
    ControlledItemManager* cim;

  protected:
    virtual cppcms::application* new_application (cppcms::service &srv) override {
      std::cout << __FUNCTION__ << ": Starting" << std::endl;
      auto app = new SignalHeadService(srv);
      app->cim = this->cim;

      return app;
    }

  };
  
  void CppCMSLoop( ControlledItemManager* cim ) {
    std::string cppcmsConfigFile = "config.js";
    cppcms::json::value config;
    {
      std::ifstream cf(cppcmsConfigFile);

      cf >> config;
    }

    booster::shared_ptr<SignalHeadServiceFactory> shsFactory(new SignalHeadServiceFactory());
    shsFactory->cim = cim;

    // Invoke with calls such as:
    // curl http://localhost:8080/son" --data '{ "method":"set", "params": [ 1, 5, 0 ], "id" : 1}'

    
    cppcms::service srv(config);
    srv.applications_pool().mount(shsFactory);
    srv.run();
  }
}
