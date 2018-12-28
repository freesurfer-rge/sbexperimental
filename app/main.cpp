#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "configreader.hpp"
#include "pinmanager.hpp"
#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "controlleditemmanager.hpp"

#include "consoleloop.hpp"
#include "cppcmsloop.hpp"

#include "cmdlineopts.hpp"
#include "outputselector.hpp"

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
    std::vector< std::unique_ptr<Signalbox::ControlledItemData> > configItems;
    cr.ReadConfiguration( configItems );

    std::cout << "Read config file" << std::endl;
    
    // -----

    Signalbox::OutputSelector* dest = Signalbox::OutputSelector::GetSelector(opts.outputDestination);
    Signalbox::PinManagerFactory* pmf = dest->GetPinManagerFactory();
    Signalbox::ControlledItemManager cim(pmf);

    auto nPopulate = cim.PopulateItems( configItems );
    std::cout << "Populated " << nPopulate << " items" << std::endl;

    auto nActivate = cim.ActivateItems();
    std::cout << "Activated " << nActivate << " items" << std::endl;

    CppCMSLoop( &cim );
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
