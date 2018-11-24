#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include <boost/program_options.hpp>

#include "configreader.hpp"
#include "outputpin.hpp"
#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "consoleloop.hpp"
#include "consoleoutputpin.hpp"

// ===================================================

int main(int ac, char* av[]) {

  try {
    std::string configFile;
    std::string configOpt = "configuration-file";
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

    // -----

    Signalbox::ConfigReader cr(configFile);
    std::vector< std::unique_ptr<Signalbox::ControlledItem> > configItems;
    cr.ReadConfiguration( configItems );

    std::cout << "Read config file" << std::endl;
    
    // -----

    Signalbox::OutputPin::sample = std::unique_ptr<Signalbox::OutputPin>(new Signalbox::ConsoleOutputPin());

    std::map<Signalbox::ItemId,std::unique_ptr<Signalbox::SignalHead>> sigs;
    for( auto it=configItems.begin();
	 it!= configItems.end();
	 ++it ) {
      Signalbox::ControlledItem* ci = (*it).get();
      Signalbox::SignalHeadData* sd = dynamic_cast<Signalbox::SignalHeadData*>( ci );
      if( sd == NULL ) {
	throw std::runtime_error("Could  not convert to SignalHeadData");
      }
      auto nxt = Signalbox::SignalHead::create(sd);
      sigs[nxt->getId()]= std::move(nxt);
    }

    std::cout << "Signals created" << std::endl;

    for( auto it=sigs.begin(); it!=sigs.end(); ++it ) {
      (*it).second->Activate();
    }

    std::cout << "Signals activated" << std::endl;

    consoleloop( sigs );
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  
  return EXIT_SUCCESS;
}
