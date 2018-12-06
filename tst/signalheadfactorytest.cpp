#include <boost/test/unit_test.hpp>

#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "signalheadfactory.hpp"

// =========================================
#include "mockpinmanagerfixture.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( SignalHeadFactory, MockPinManagerFixture )

BOOST_AUTO_TEST_CASE( SimpleConstruct )
{
  Signalbox::SignalHeadFactory shf(&(this->mpm));

  const std::string redPin = "12";
  const std::string greenPin = "15";
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::ControlledItem> ci;
  ci = shf.Manufacture(&sd);
  BOOST_REQUIRE(ci);
  BOOST_CHECK_EQUAL( ci->getId(), sd.id );

  Signalbox::SignalHead *sig;
  sig = dynamic_cast<Signalbox::SignalHead*>(ci.get());
  BOOST_REQUIRE(sig);
 // Check both pins have been created
  BOOST_CHECK_EQUAL( this->mpm.DigitalOutputPinCount(), 2 );

  // Red pin as expected - and on
  auto red = this->mpm.FetchMockDigitalOutputPin(redPin);
  BOOST_REQUIRE( red );
  BOOST_CHECK( red->Get() );

  // Green pin as expected - and off
  auto green = this->mpm.FetchMockDigitalOutputPin(greenPin);
  BOOST_REQUIRE( green );
  BOOST_CHECK( !green->Get() );
}

BOOST_AUTO_TEST_SUITE_END()
