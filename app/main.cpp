#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "configuration/configreader.hpp"

#include "railtrafficcontrolclient.hpp"
#include "railtrafficcontroldata.hpp"

#include "pinmanager.hpp"
#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "controlleditemmanager.hpp"

#include "cmdlineopts.hpp"
#include "outputselector.hpp"
#include "driverselector.hpp"
#include "rtcselector.hpp"

// ===================================================

int main(int ac, char* av[]) {

  try {
    Signalbox::CmdLineOpts opts;

    opts.Populate(ac, av);
    if( opts.helpMessagePrinted ) {
      return EXIT_SUCCESS;
    }
    
    // -----

    Signalbox::Configuration::ConfigReader cr(opts.configFilePath);
    std::vector< std::unique_ptr<Signalbox::ControlledItemData> > configItems;
    cr.ReadControlledItems( configItems );

    Signalbox::RailTrafficControlData rtcData;
    cr.ReadRailTrafficControl( rtcData );

    Signalbox::I2CBusData i2cBusData;
    cr.ReadI2CData( i2cBusData );

    std::cout << "Read config file" << std::endl;
    
    // -----
    Signalbox::RTCSelector* rtcs = Signalbox::RTCSelector::GetSelector(opts.rtcClient);
    Signalbox::RailTrafficControlClientFactory* rtcFactory = rtcs->GetRailTrafficControlClientFactory();
    auto rtcClient = rtcFactory->Create(rtcData);

    Signalbox::OutputSelector* dest = Signalbox::OutputSelector::GetSelector(opts.outputDestination);
    Signalbox::PinManagerFactory* pmf = dest->GetPinManagerFactory();
    Signalbox::ControlledItemManager cim(pmf, rtcClient);

    cim.Initialise( i2cBusData );
    
    auto nPopulate = cim.PopulateItems( configItems );
    std::cout << "Populated " << nPopulate << " items" << std::endl;

    auto nActivate = cim.ActivateItems();
    std::cout << "Activated " << nActivate << " items" << std::endl;

    Signalbox::DriverSelector *drvSelector = Signalbox::DriverSelector::GetSelector(opts.driver);
    Signalbox::ControlledItemDriver* drv = drvSelector->GetDriver();
    
    drv->Run( &cim );
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
