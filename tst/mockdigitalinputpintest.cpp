#include <thread>

#include <boost/test/unit_test.hpp>

#include "mockdigitalinputpin.hpp"

// =========================================
#include "mockpinmanagerfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( MockDigitalInputPin, MockPinManagerFixture )

BOOST_AUTO_TEST_CASE( GetAndSet )
{
  Signalbox::DigitalInputPinData data;
  data.id = "AnyId";
  data.settings["First"] = "0";

  auto dip = this->pm->CreateDigitalInputPin(data);
  BOOST_REQUIRE(dip);

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE(mdip);
  BOOST_CHECK_EQUAL(mdip->id, "AnyId" );

  BOOST_CHECK_EQUAL( mdip->Get(), false );
  mdip->Set(true);
  BOOST_CHECK_EQUAL( mdip->Get(), true );
  mdip->Set(false);
  BOOST_CHECK_EQUAL( mdip->Get(), false);
}

BOOST_AUTO_TEST_CASE( WaitAndNotify, *boost::unit_test::timeout(5) )
{
  Signalbox::DigitalInputPinData data;
  data.id = "AnyId";
  data.settings["Another"] = "0";
  
  auto notifyDelay = std::chrono::seconds(2);

  auto dip = this->pm->CreateDigitalInputPin(data);
  BOOST_REQUIRE(dip);

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE(mdip);
  BOOST_CHECK_EQUAL( mdip->id, "AnyId" );
  BOOST_CHECK_EQUAL( mdip->createSettings.at("Another"), "0" );

  auto start = std::chrono::system_clock::now();
  // Spin off a thread which will notify us after a set time
  std::thread notifyThread( [notifyDelay,mdip]() { std::this_thread::sleep_for(notifyDelay); mdip->Set(true); } );
  notifyThread.detach();

  // Wait on the notification
  bool res = dip->Wait();
  auto stop = std::chrono::system_clock::now();

  // Check that we got the right result
  BOOST_CHECK_EQUAL( res, true );
  // Check that there was a delay on the notification
  BOOST_CHECK( (stop-start) >= notifyDelay );
}


BOOST_AUTO_TEST_CASE( WaitForNoChange, *boost::unit_test::timeout(5) )
{
  Signalbox::DigitalInputPinData data;
  data.id = "AnyOtherId";
  data.settings["First"] = "0";
  
  auto waitInterval = std::chrono::seconds(2);

  auto dip = this->pm->CreateDigitalInputPin(data);
  BOOST_REQUIRE(dip);
  BOOST_CHECK_EQUAL( dip->Get(), false );

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE(mdip);
  BOOST_CHECK_EQUAL( mdip->id, "AnyOtherId" );

  auto start = std::chrono::system_clock::now();
  bool res = dip->WaitFor( waitInterval );
  auto stop = std::chrono::system_clock::now();

  // No change on the pin state
  BOOST_CHECK_EQUAL( res, false );
  // Check we waited long enough
  BOOST_CHECK( (stop-start) >= waitInterval );

  // Repeat with the pin set to true
  mdip->Set(true);
  BOOST_CHECK_EQUAL( dip->Get(), true );

  start = std::chrono::system_clock::now();
  res = dip->WaitFor( waitInterval );
  stop = std::chrono::system_clock::now();

  BOOST_CHECK_EQUAL( res, true );
  BOOST_CHECK( (stop-start) >= waitInterval );
}

BOOST_AUTO_TEST_CASE( WaitForChange, *boost::unit_test::timeout(5) )
{
  Signalbox::DigitalInputPinData data;
  data.id = "SomeOtherId";
  data.settings["YASetting"] = "0112221";
  
  auto waitInterval = std::chrono::seconds(3);
  auto notifyDelay = std::chrono::seconds(1);
  BOOST_REQUIRE( waitInterval > notifyDelay );

  auto dip = this->pm->CreateDigitalInputPin(data);
  BOOST_REQUIRE(dip);
  BOOST_CHECK_EQUAL( dip->Get(), false );

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE(mdip);
  BOOST_CHECK_EQUAL(mdip->id, "SomeOtherId" );
  BOOST_CHECK_EQUAL(mdip->createSettings.at("YASetting"), "0112221");
  
  auto start = std::chrono::system_clock::now();
  // Spin off a thread which will notify us after a set time
  std::thread notifyThread( [notifyDelay,mdip]() { std::this_thread::sleep_for(notifyDelay); mdip->Set(true); } );
  notifyThread.detach();

  // Wait on the notification
  bool res = dip->WaitFor(waitInterval);
  auto stop = std::chrono::system_clock::now();

  // Check that we got the right result
  BOOST_CHECK_EQUAL( res, true );
  // Check that there was a delay on the notification
  BOOST_CHECK( (stop-start) >= notifyDelay );
  BOOST_CHECK( (stop-start) <= waitInterval );
}
  
BOOST_AUTO_TEST_SUITE_END()
