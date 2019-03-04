#include <boost/test/unit_test.hpp>

#include "trackcircuitmonitor.hpp"

#include "mocktrackcircuitmonitorfactoryfixture.hpp"

// ============================================

void PauseForTrackCircuitMonitor() {
  // We don't have visibility into the internal thread
  // of the TrackCircuitMonitor
  // In testing, we wait a short time to allow for updates
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// ============================================

BOOST_FIXTURE_TEST_SUITE( TrackCircuitMonitor, MockTrackCircuitMonitorFactoryFixture )

BOOST_AUTO_TEST_CASE( LifeCycle )
{
  const std::string pinId = "GPIO25";
  Signalbox::TrackCircuitMonitorData tcmd;
  tcmd.id = Signalbox::ItemId::Random();
  tcmd.inputPin.id = pinId;
  tcmd.inputPin.settings["SomeKey"] = "SomeValue";

  std::unique_ptr<Signalbox::TrackCircuitMonitor> tcm;
  tcm = this->CreateTrackCircuitMonitor(tcmd);
  BOOST_REQUIRE( tcm );

  BOOST_CHECK_EQUAL( this->mpm.DigitalInputPinCount(), 1 );

  tcm->Activate();

  BOOST_CHECK_EQUAL( tcm->Get(), false );
  BOOST_CHECK_EQUAL( this->rtc.lastItem, 0 );
  
  auto pin = this->mpm.FetchMockDigitalInputPin( pinId );
  BOOST_REQUIRE( pin );
  BOOST_CHECK_EQUAL( pin->createSettings.size(), 1 );
  BOOST_CHECK_EQUAL( pin->createSettings.at("SomeKey"), "SomeValue" );
}

BOOST_AUTO_TEST_CASE( SetToOccupiedAndUnoccupied )
{
  const std::string pinId = "GPIO25";
  Signalbox::TrackCircuitMonitorData tcmd;
  tcmd.id = Signalbox::ItemId::Random();
  tcmd.inputPin.id = pinId;
  tcmd.inputPin.settings["SomeKey"] = "SomeValue";

  std::unique_ptr<Signalbox::TrackCircuitMonitor> tcm;
  tcm = this->CreateTrackCircuitMonitor(tcmd);
  BOOST_REQUIRE( tcm );
  tcm->Activate();

  auto pin = this->mpm.FetchMockDigitalInputPin( pinId );
  BOOST_REQUIRE( pin );
  BOOST_CHECK_EQUAL( tcm->Get(), false );
  
  pin->Set( true );
  PauseForTrackCircuitMonitor();
  BOOST_CHECK_EQUAL( tcm->Get(), true );
  BOOST_CHECK_EQUAL( this->rtc.lastItem, tcmd.id );
  BOOST_CHECK_EQUAL( this->rtc.lastOccupy, true );

  this->rtc.lastItem = 0;

  pin->Set( false );
  PauseForTrackCircuitMonitor();
  BOOST_CHECK_EQUAL( tcm->Get(), false );
  BOOST_CHECK_EQUAL( this->rtc.lastItem, tcmd.id );
  BOOST_CHECK_EQUAL( this->rtc.lastOccupy, false );
}

BOOST_AUTO_TEST_CASE( CheckSingleNotification )
{
  const std::string pinId = "GPIO01";
  Signalbox::TrackCircuitMonitorData tcmd;
  tcmd.id = Signalbox::ItemId::Random();
  tcmd.inputPin.id = pinId;

  std::unique_ptr<Signalbox::TrackCircuitMonitor> tcm;
  tcm = this->CreateTrackCircuitMonitor(tcmd);
  BOOST_REQUIRE( tcm );
  tcm->Activate();
  BOOST_CHECK_EQUAL( tcm->Get(), false );

  auto pin = this->mpm.FetchMockDigitalInputPin( pinId );
  BOOST_REQUIRE( pin );

  pin->Set( true );
  PauseForTrackCircuitMonitor();
  BOOST_CHECK_EQUAL( tcm->Get(), true );
  BOOST_CHECK_EQUAL( this->rtc.lastItem, tcmd.id );
  BOOST_CHECK_EQUAL( this->rtc.lastOccupy, true );

  // Deliberately change rtc
  this->rtc.lastItem = 0;
  this->rtc.lastOccupy = false;

  pin->Set( true );
  PauseForTrackCircuitMonitor();
  BOOST_CHECK_EQUAL( tcm->Get(), true );
  // rtc should be unchanged since this was a repeat
  BOOST_CHECK_EQUAL( this->rtc.lastItem, 0 );
  BOOST_CHECK_EQUAL( this->rtc.lastOccupy, false );
}

BOOST_AUTO_TEST_SUITE_END()
