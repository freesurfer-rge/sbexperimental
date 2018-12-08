#include <boost/test/unit_test.hpp>

#include "controlleditemmanager.hpp"
#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "mockpinmanager.hpp"

// =========================================
#include "mockpinmanagerfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( ControlledItemManager, MockPinManagerFixture )

// =========================================

BOOST_AUTO_TEST_SUITE( ControlledItemFactorySelector )

BOOST_AUTO_TEST_CASE( GetSignalHeadFactory )
{
  Signalbox::ControlledItemManager cim(this->pm);

  auto res = cim.GetSignalHeadFactory();
  BOOST_REQUIRE(res);

  auto shf = dynamic_cast<Signalbox::SignalHeadFactory*>(res);
  BOOST_REQUIRE(shf);
}

BOOST_AUTO_TEST_SUITE_END()

// =========================================

BOOST_AUTO_TEST_SUITE( CreateItem )

BOOST_AUTO_TEST_CASE( CreateSignal )
{
  Signalbox::ControlledItemManager cim(this->pm);

  const std::string redPin = "12";
  const std::string greenPin = "15";
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;

  std::unique_ptr<Signalbox::ControlledItem> ci;
  ci = cim.CreateItem(&sd);
  BOOST_REQUIRE(ci);

  BOOST_CHECK_EQUAL( ci->getId(), sd.id );

  Signalbox::SignalHead *sig(NULL);
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

BOOST_AUTO_TEST_SUITE_END()
