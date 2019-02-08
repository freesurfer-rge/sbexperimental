#include <boost/test/unit_test.hpp>

#include "mockrailtrafficcontrolclient.hpp"
#include "mockrailtrafficcontrolclientfactory.hpp"

BOOST_AUTO_TEST_SUITE( MockRailTrafficControlClient )

BOOST_AUTO_TEST_CASE( Construct )
{
  Signalbox::RailTrafficControlData rtcData;
  rtcData.host = std::string("waterloo.local");
  rtcData.port = 10001;
  
  Signalbox::MockRailTrafficControlClientFactory mockFactory;
  auto rtcClient = mockFactory.Create(rtcData);
  auto mrtcc = dynamic_cast<Signalbox::MockRailTrafficControlClient*>(rtcClient.get());

  BOOST_CHECK_EQUAL( mrtcc->host, rtcData.host );
  BOOST_CHECK_EQUAL( mrtcc->port, rtcData.port );
}

BOOST_AUTO_TEST_CASE( GetAndSet )
{
  Signalbox::RailTrafficControlData rtcData;
  rtcData.host = std::string("kingsx.local");
  rtcData.port = 10001;
  
  Signalbox::MockRailTrafficControlClientFactory mockFactory;
  auto rtcClient = mockFactory.Create(rtcData);
  auto mrtcc = dynamic_cast<Signalbox::MockRailTrafficControlClient*>(rtcClient.get());

  Signalbox::ItemId firstId(10);
  Signalbox::ItemId secondId(20);
  
  rtcClient->SendTrackCircuitNotification( firstId, true );
  BOOST_CHECK_EQUAL( mrtcc->lastItem, firstId );
  BOOST_CHECK_EQUAL( mrtcc->lastOccupy, true );

  rtcClient->SendTrackCircuitNotification( secondId, false );
  BOOST_CHECK_EQUAL( mrtcc->lastItem, secondId );
  BOOST_CHECK_EQUAL( mrtcc->lastOccupy, false );
}

BOOST_AUTO_TEST_SUITE_END()
