#include <iostream>

#include <boost/program_options.hpp>

#include "cmdlineopts.hpp"

#include "outputselector.hpp"
#include "driverselector.hpp"
#include "rtcselector.hpp"

// -------------------------

namespace bpo = boost::program_options;

// -------------------------

namespace Signalbox {
  void CmdLineOpts::Populate( int argc, char* argv[] ) {
    std::string configOpt = "configuration-file";
    std::string outputOpt = "pinmanager";
    std::string driverOpt = "driver";
    std::string rtcOpt = "rtc";

    bpo::options_description desc("Allowed Options");
    desc.add_options()
      ("help", "Show help message")
      ((configOpt+",f").c_str(), bpo::value<std::string>(&(this->configFilePath)), "Path to configuration XML file")
      ;
    
    std::string outputDests = OutputSelector::ListOutputSelectors();
    std::string outputDesc = std::string("Choice of PinManager (") + outputDests + ")";
    desc.add_options()
      ((outputOpt+",p").c_str(), bpo::value<std::string>(&(this->outputDestination)), outputDesc.c_str());

    std::string drivers = DriverSelector::ListDriverSelectors();
    std::string driverDesc = std::string("Choice of driver (") + drivers + ")";
    desc.add_options()
      ((driverOpt+",d").c_str(), bpo::value<std::string>(&(this->driver)), driverDesc.c_str());

    std::string rtcClients = RTCSelector::ListRTCSelectors();
    std::string rtcDesc = std::string("Choice of RTC (") + rtcClients + ")";
    desc.add_options()
      ((rtcOpt+",r").c_str(), bpo::value<std::string>(&(this->rtcClient)), rtcDesc.c_str());
    
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);
    
    if( vm.count("help") ) {
      std::cout << desc << std::endl;
      this->helpMessagePrinted = true;
      return;
    }
    
    if( vm.count(configOpt.c_str()) ) {
      std::cout << "Configuration file: " << this->configFilePath << std::endl;
    } else {
      throw std::runtime_error("Configuration file not specified");
    }

    if( vm.count(outputOpt.c_str()) ) {
      std::cout << "Output destination: " << this->outputDestination << std::endl;
    } else {
      throw std::runtime_error("Output option not specified");
    }

    if( vm.count(driverOpt.c_str()) ) {
      std::cout << "Driver: " <<  this->driver << std::endl;
    } else {
      throw std::runtime_error("Driver option not specified");
    }
  
    if( vm.count(rtcOpt.c_str()) ) {
      std::cout << "RTC: " <<  this->rtcClient << std::endl;
    } else {
      throw std::runtime_error("RTC option not specified");
    }
  }
}
