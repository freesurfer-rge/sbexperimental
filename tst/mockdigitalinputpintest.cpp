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
  const std::string anyId = "AnyId";

  auto dip = this->pm->CreateDigitalInputPin(anyId);
  BOOST_REQUIRE(dip);

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE(mdip);

  BOOST_CHECK_EQUAL( mdip->Get(), false );
  mdip->Set(true);
  BOOST_CHECK_EQUAL( mdip->Get(), true );
  mdip->Set(false);
  BOOST_CHECK_EQUAL( mdip->Get(), false);
}

BOOST_AUTO_TEST_CASE( WaitAndNotify, *boost::unit_test::timeout(5) )
{
  const std::string anyId = "AnyId";
  auto notifyDelay = std::chrono::seconds(2);

  auto dip = this->pm->CreateDigitalInputPin(anyId);
  BOOST_REQUIRE(dip);

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE(mdip);

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

BOOST_AUTO_TEST_SUITE_END()
