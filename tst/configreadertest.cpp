#include <boost/test/unit_test.hpp>

#include "xercesguard.hpp"

#include "configreader.hpp"

#include "signalheaddata.hpp"

// =====================================================

const std::string singlesignalfile = "singlesignalhead.xml";
const std::string twosignalfile = "twosignalheads.xml";

// =====================================================

BOOST_AUTO_TEST_SUITE( ConfigReader )

BOOST_AUTO_TEST_CASE( ConstructorThrowsOnBadFilename )
{
  BOOST_CHECK_THROW( Signalbox::ConfigReader("NoSuchFile.xml"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( ConstructorCompletes )
{
  BOOST_CHECK_NO_THROW( Signalbox::ConfigReader cr(singlesignalfile) );
}

BOOST_AUTO_TEST_CASE( ReadSingleSignal )
{
  Signalbox::ConfigReader cr(singlesignalfile);

  std::vector< std::unique_ptr<Signalbox::ControlledItem> > configItems;

  cr.ReadConfiguration( configItems );

  BOOST_CHECK_EQUAL( configItems.size(), 1 );
  
  Signalbox::ItemId expectedId;
  expectedId.Parse("00:00:00:01");

  Signalbox::ControlledItem* item = configItems.at(0).get();
  BOOST_CHECK_EQUAL( item->id, expectedId );

  Signalbox::SignalHeadData* sig;
  sig = dynamic_cast<Signalbox::SignalHeadData*>(item);
  BOOST_REQUIRE( sig != nullptr );

  BOOST_CHECK_EQUAL( sig->aspectCount, 4 );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Red], 02 );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Yellow1], 21 );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Yellow2], 16 );
  BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Green], 05 );
}

BOOST_AUTO_TEST_CASE( ReadTwoSignals )
{
  Signalbox::ConfigReader cr(twosignalfile);

  std::vector< std::unique_ptr<Signalbox::ControlledItem> > configItems;

  cr.ReadConfiguration( configItems );

  BOOST_CHECK_EQUAL( configItems.size(), 2 );

  for( auto it = configItems.begin(); it!=configItems.end(); ++it ) {
    Signalbox::SignalHeadData* sig( dynamic_cast<Signalbox::SignalHeadData*>(it->get()) );
    BOOST_REQUIRE_NE( sig, nullptr );
    
    if( sig->id == Signalbox::ItemId(1) ) {
      BOOST_CHECK_EQUAL( sig->aspectCount, 2 );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Red], 02 );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Green], 05 );
    } else if( sig->id == Signalbox::ItemId(2) ) {
      BOOST_CHECK_EQUAL( sig->aspectCount, 3 );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Red], 03 );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Yellow1], 04 );
      BOOST_CHECK_EQUAL( sig->pinData[Signalbox::SignalHeadPins::Green], 06 );

    } else {
      BOOST_FAIL("Bad ItemId detected");
    }
  }
}

BOOST_AUTO_TEST_SUITE_END();
