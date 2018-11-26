#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "configreader.hpp"
#include "outputpin.hpp"
#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "consoleloop.hpp"
#include "consoleoutputpin.hpp"

#include "cmdlineopts.hpp"

// ===================================================

int main(int ac, char* av[]) {

  try {
    Signalbox::CmdLineOpts opts;

    opts.Populate(ac, av);
    if( opts.helpMessagePrinted ) {
      return EXIT_SUCCESS;
    }
    
    // -----

    Signalbox::ConfigReader cr(opts.configFilePath);
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
	throw std::runtime_error("Could not convert to SignalHeadData");
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
