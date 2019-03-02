#include <boost/test/unit_test.hpp>

#include "trackcircuitmonitor.hpp"
#include "trackcircuitmonitordata.hpp"

#include "trackcircuitmonitorfactory.hpp"

#include "mockrailtrafficcontrolclient.hpp"

// =========================================
#include "badcontrolleditemdata.hpp"
#include "mockpinmanagerfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( TrackCircuitMonitorFactory, MockPinManagerFixture )

BOOST_AUTO_TEST_CASE( Manufacture )
{
  Signalbox::MockRailTrafficControlClient mockRTC;
  Signalbox::TrackCircuitMonitorFactory tcmf(&(this->mpm), &mockRTC );

  const std::string pinId = "GPIO25";
  Signalbox::TrackCircuitMonitorData tcmd;
  tcmd.id = Signalbox::ItemId::Random();
  tcmd.inputPin.id = pinId;
  tcmd.inputPin.settings["MySetting"] = "Something";

  auto ci = tcmf.Manufacture(&tcmd);
  BOOST_REQUIRE(ci);
  BOOST_CHECK_EQUAL( ci->getId(), tcmd.id );

  Signalbox::TrackCircuitMonitor* tcm(NULL);
  tcm = dynamic_cast<Signalbox::TrackCircuitMonitor*>(ci.get());
  BOOST_REQUIRE(tcm);

  // Check pin created
  BOOST_CHECK_EQUAL( this->mpm.DigitalInputPinCount(), 1 );
  auto pin = this->mpm.FetchMockDigitalInputPin(pinId);
  BOOST_REQUIRE( pin );
  BOOST_CHECK_EQUAL( pin->Get(), false );

  BOOST_CHECK_EQUAL( tcm->Get(), false );
  BOOST_CHECK_EQUAL( tcm->getTypeString(), "trackcircuitmonitor" );
}

BOOST_AUTO_TEST_CASE( BadData )
{
  BadControlledItemData bd;

  Signalbox::MockRailTrafficControlClient mockRTC;
  Signalbox::TrackCircuitMonitorFactory tcmf(&(this->mpm), &mockRTC );

  std::string msg("Failed to cast ControlledItemData to TrackCircuitMonitorData");
  BOOST_CHECK_EXCEPTION( tcmf.Manufacture(&bd),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}


BOOST_AUTO_TEST_SUITE_END()
