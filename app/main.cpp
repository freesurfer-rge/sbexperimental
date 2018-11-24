#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/program_options.hpp>

int main(int ac, char* av[]) {
  try {
    std::string configOpt = "configuration-file";
    std::string configFile;
    namespace bpo = boost::program_options;
    
    bpo::options_description desc("Allowed Options");
    desc.add_options()
      ("help", "Show help message")
      ((configOpt+",f").c_str(), bpo::value<std::string>(&configFile), "Path to configuration XML file")
      ;
    
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(ac, av, desc), vm);
    bpo::notify(vm);
    
    if( vm.count("help") ) {
      std::cout << desc << std::endl;
      return EXIT_SUCCESS;
    }
    
    if( vm.count(configOpt.c_str()) ) {
      std::cout << "Configuration file: " << configFile << std::endl;
    } else {
      throw std::runtime_error("Configuration file not specified");
    }
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
