#include <iostream>

#include <boost/program_options.hpp>

#include "cmdlineopts.hpp"

#include "outputselector.hpp"

// -------------------------

namespace bpo = boost::program_options;

// -------------------------

namespace Signalbox {
  void CmdLineOpts::Populate( int argc, char* argv[] ) {
    std::string configOpt = "configuration-file";
    std::string outputOpt = "output";

    bpo::options_description desc("Allowed Options");
    desc.add_options()
      ("help", "Show help message")
      ((configOpt+",f").c_str(), bpo::value<std::string>(&(this->configFilePath)), "Path to configuration XML file")
      ;
    
    std::string outputDests = OutputSelector::ListOutputSelectors();
    std::string outputDesc = std::string("Output destination (") + outputDests + ")";
    desc.add_options()
      ((outputOpt+",o").c_str(), bpo::value<std::string>(&(this->outputDestination)), outputDesc.c_str());
    
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
  }
}
