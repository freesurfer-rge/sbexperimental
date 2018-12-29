#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>
#include <cppcms/rpc_json.h>
#include <cppcms/url_dispatcher.h>  
#include <cppcms/url_mapper.h>  

#include "signalhead.hpp"

#include "cppcmsloop.hpp"


namespace cppcms {
  namespace json {
    
    template<>
    struct traits<Signalbox::SignalHead> {
      static Signalbox::SignalHead get(value const& v) {
	throw std::runtime_error("get SignalHead from JSON not supported");
      }

      static void set(value& v, Signalbox::SignalHead const& sh ) {
	std::stringstream s;
	s << sh.getId();
	v.set("id", s.str());
	v.set("aspectCount", sh.getAspectCount());
	v.set("aspect", Signalbox::ToString(sh.getAspect()));
	v.set("flash", Signalbox::ToString(sh.getFlash()));
      }
    };
  }
}

namespace Signalbox {
  class ControlledItemService : public cppcms::rpc::json_rpc_server {
  public:
    ControlledItemService(cppcms::service& srv)
      : cppcms::rpc::json_rpc_server(srv) {
      bind("setsignal", cppcms::rpc::json_method(&ControlledItemService::SetSignal, this), method_role);
      bind("getsignal", cppcms::rpc::json_method(&ControlledItemService::GetSignal, this), method_role);
    }

    void SetSignal( int id, int aspect, int flashing ) {
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
	return_error("An error occurred");
      }
      return_result("State set");
    }

    void GetSignal( int id ) {
      // Sample call:
      // curl http://localhost:8080 -H "Content-Type: application/json" --data '{ "method":"getsignal", "params": [ 2 ], "id" : 1}'
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

      return_result(*sh);
    }
    
    ControlledItemManager* cim;
  };

  class ControlledItemServiceFactory : public cppcms::application_specific_pool {
  public:
    ControlledItemServiceFactory( ControlledItemManager* cim ) :
      cppcms::application_specific_pool(),
      manager(cim) {}

  protected:
    virtual cppcms::application* new_application (cppcms::service &srv) override {
      std::cout << __PRETTY_FUNCTION__ << ": Starting" << std::endl;
      auto app = new ControlledItemService(srv);
      app->cim = this->manager;

      return app;
    }
    
  private:
    ControlledItemManager* manager;
  };
  
  void CppCMSLoop( ControlledItemManager* cim ) {
    std::string cppcmsConfigFile = "config.js";
    cppcms::json::value config;
    {
      std::ifstream cf(cppcmsConfigFile);

      cf >> config;
    }

    booster::shared_ptr<ControlledItemServiceFactory> cisFactory(new ControlledItemServiceFactory(cim));

    // Invoke with calls such as:
    // curl http://localhost:8080/signalhead -H "Content-Type: application/json" --data '{ "method":"set", "params": [ 1, 5, 0 ], "id" : 1}'
    
    cppcms::service srv(config);
    srv.applications_pool().mount(cisFactory);
    srv.run();
  }
}
