#include <boost/test/unit_test.hpp>


#include "configuration/configreader.hpp"

#include "signalheaddata.hpp"
#include "trackcircuitmonitordata.hpp"
#include "railtrafficcontroldata.hpp"

#include "exceptionmessagecheck.hpp"

// =====================================================

const std::string singlesignalfile = "singlesignalhead.xml";
const std::string twosignalfile = "twosignalheads.xml";

const std::string singletrackcircuitfile = "singletrackcircuitmonitor.xml";

// =====================================================

BOOST_AUTO_TEST_SUITE( ConfigReader )

BOOST_AUTO_TEST_CASE( ConstructorThrowsOnBadFilename )
{
  BOOST_CHECK_THROW( Signalbox::Configuration::ConfigReader("NoSuchFile.xml"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( ConstructorCompletes )
{
  BOOST_CHECK_NO_THROW( Signalbox::Configuration::ConfigReader cr(singlesignalfile) );
}

BOOST_AUTO_TEST_SUITE( ReadSignalHeadData )

BOOST_AUTO_TEST_CASE( ReadSingleSignal )
{
  Signalbox::Configuration::ConfigReader cr(singlesignalfile);

  std::vector< std::unique_ptr<Signalbox::ControlledItemData> > configItems;

  cr.ReadControlledItems( configItems );

  BOOST_CHECK_EQUAL( configItems.size(), 1 );
  
  Signalbox::ItemId expectedId;
  expectedId.Parse("00:00:00:01");

  Signalbox::ControlledItemData* item = configItems.at(0).get();
  BOOST_CHECK_EQUAL( item->id, expectedId );

  Signalbox::SignalHeadData* sig;
  sig = dynamic_cast<Signalbox::SignalHeadData*>(item);
  BOOST_REQUIRE( sig != nullptr );

  BOOST_CHECK_EQUAL( sig->aspectCount, 4 );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Red], "GPIO02" );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Yellow1], "GPIO21" );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Yellow2], "GPIO16" );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Green], "GPIO05" );
}

BOOST_AUTO_TEST_CASE( ReadTwoSignals )
{
  Signalbox::Configuration::ConfigReader cr(twosignalfile);

  std::vector< std::unique_ptr<Signalbox::ControlledItemData> > configItems;

  cr.ReadControlledItems( configItems );

  BOOST_CHECK_EQUAL( configItems.size(), 2 );

  for( auto it = configItems.begin(); it!=configItems.end(); ++it ) {
    Signalbox::SignalHeadData* sig( dynamic_cast<Signalbox::SignalHeadData*>(it->get()) );
    BOOST_REQUIRE_NE( sig, nullptr );
    
    if( sig->id == Signalbox::ItemId(1) ) {
      BOOST_CHECK_EQUAL( sig->aspectCount, 2 );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Red], "GPIO02" );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Green], "GPIO05" );
    } else if( sig->id == Signalbox::ItemId(2) ) {
      BOOST_CHECK_EQUAL( sig->aspectCount, 3 );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Red], "GPIO03" );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Yellow1], "GPIO04" );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Green], "GPIO06" );

    } else {
      BOOST_FAIL("Bad ItemId detected");
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

// =============================================================

BOOST_AUTO_TEST_SUITE( ReadTrackCircuitMonitorData )

BOOST_AUTO_TEST_CASE( SingleTrackCircuit )
{
  Signalbox::Configuration::ConfigReader cr(singletrackcircuitfile);

  std::vector< std::unique_ptr<Signalbox::ControlledItemData> > configItems;

  cr.ReadControlledItems( configItems );

  BOOST_REQUIRE_EQUAL( configItems.size(), 1 );
  
  Signalbox::ItemId expectedId;
  expectedId.Parse("00:00:00:aa");

  Signalbox::ControlledItemData* item = configItems.at(0).get();
  BOOST_CHECK_EQUAL( item->id, expectedId );

  Signalbox::TrackCircuitMonitorData* tcmd;
  tcmd = dynamic_cast<Signalbox::TrackCircuitMonitorData*>(item);
  BOOST_REQUIRE(tcmd);

  BOOST_CHECK_EQUAL( tcmd->inputPin.id, "GPIO03" );
  BOOST_CHECK_EQUAL( tcmd->inputPin.sensor, "occupancy" );
  BOOST_REQUIRE_EQUAL( tcmd->inputPin.settings.size(), 1 );
  BOOST_CHECK_EQUAL( tcmd->inputPin.settings.at("glitch"), "10000" );
}

BOOST_AUTO_TEST_SUITE_END()

// =============================================================

BOOST_AUTO_TEST_SUITE( ReadRailTrafficControlData )
  
BOOST_AUTO_TEST_CASE( ReadRTC )
{
  Signalbox::Configuration::ConfigReader cr(singlesignalfile);

  Signalbox::RailTrafficControlData rtcData;

  cr.ReadRailTrafficControl( rtcData );
  
  BOOST_CHECK_EQUAL( rtcData.host, "rtc.local" );
  BOOST_CHECK_EQUAL( rtcData.port, 8008 );
}

BOOST_AUTO_TEST_CASE( PortTooBig )
{
  Signalbox::Configuration::ConfigReader cr(twosignalfile);

  Signalbox::RailTrafficControlData rtcData;

  std::string msg("Invalid Port for RailTrafficControl");
  BOOST_CHECK_EXCEPTION( cr.ReadRailTrafficControl( rtcData ),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE_END()
