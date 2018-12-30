#include <cppcms/service.h>
#include <cppcms/json.h>

#include "controlleditemservicefactory.hpp"

#include "cppcmsdriver.hpp"

namespace Signalbox {
  void CPPCMSDriver::Run(ControlledItemFetcher* f) {
    cppcms::json::value config;
    config["service"]["ip"] = "0.0.0.0"; // Use 127.0.0.1 to restrict access to localhost
    config["service"]["api"] = "http"; // Be a webserver
    config["service"]["port"] = 8080;
    config["http"]["script"] = "/rpc";
    config["logging"]["level"] = "debug";

    // Enable serving of plain documents from the 'html' directory
    config["file_server"]["enable"] = true;
    config["file_server"]["document_root"] = "html";

    booster::shared_ptr<ControlledItemServiceFactory> cisFactory(new ControlledItemServiceFactory(f));
    cppcms::service srv(config);
    srv.applications_pool().mount(cisFactory);
    srv.run();
  }
}
