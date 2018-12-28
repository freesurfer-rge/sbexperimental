#include <iostream>
#include <fstream>
#include <string>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/rpc_json.h>

#include "cppcmsloop.hpp"

namespace Signalbox {
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
