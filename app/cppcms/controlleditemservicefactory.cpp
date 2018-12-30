#include "controlleditemservice.hpp"

#include "controlleditemservicefactory.hpp"

namespace Signalbox {
  cppcms::application* ControlledItemServiceFactory::new_application (cppcms::service &srv) {
    auto app = new ControlledItemService(srv);
    app->cif = this->fetcher;
    
    return app;
  }
}
