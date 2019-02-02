#include <boost/test/unit_test.hpp>

#include "mockrailtrafficcontrolclient.hpp"

BOOST_AUTO_TEST_SUITE( MockRailTrafficControlClient )

BOOST_AUTO_TEST_CASE( GetAndSet )
{
  Signalbox::MockRailTrafficControlClient mrtcc;

  Signalbox::ItemId firstId(10);
  Signalbox::ItemId secondId(20);
  
  mrtcc.SendTrackCircuitNotification( firstId, true );
  BOOST_CHECK_EQUAL( mrtcc.lastItem, firstId );
  BOOST_CHECK_EQUAL( mrtcc.lastOccupy, true );

  mrtcc.SendTrackCircuitNotification( secondId, false );
  BOOST_CHECK_EQUAL( mrtcc.lastItem, secondId );
  BOOST_CHECK_EQUAL( mrtcc.lastOccupy, false );
}

BOOST_AUTO_TEST_SUITE_END();
