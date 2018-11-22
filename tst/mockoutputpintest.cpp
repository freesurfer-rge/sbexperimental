#include <boost/test/unit_test.hpp>

#include "mockoutputpin.hpp"

#include "mockoutputpinfixture.hpp"

BOOST_FIXTURE_TEST_SUITE( MockOutputPin, MockOutputPinFixture )

BOOST_AUTO_TEST_CASE( Manufacture )
{
  Signalbox::OutputPin::sample = std::unique_ptr<Signalbox::OutputPin>(new Signalbox::MockOutputPin());

  const char anyPin = 10;

  auto res = Signalbox::OutputPin::create(anyPin);

  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 1 );
  
  Signalbox::MockOutputPin* resMock = dynamic_cast<Signalbox::MockOutputPin*>(res.get());
  BOOST_REQUIRE( resMock );
  BOOST_CHECK_EQUAL( resMock->pin, anyPin );
  BOOST_CHECK_EQUAL( resMock, Signalbox::MockOutputPin::allPins[anyPin] );
  BOOST_CHECK( !resMock->isOn );
}

BOOST_AUTO_TEST_CASE( TurnOnOff )
{
  Signalbox::OutputPin::sample = std::unique_ptr<Signalbox::OutputPin>(new Signalbox::MockOutputPin());

  const char anyPin = 11;

  auto res = Signalbox::OutputPin::create(anyPin);
  
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 1 );

  Signalbox::MockOutputPin* resMock = dynamic_cast<Signalbox::MockOutputPin*>(res.get());
  BOOST_REQUIRE( resMock );
  BOOST_CHECK_EQUAL( resMock, Signalbox::MockOutputPin::allPins[anyPin] );

  BOOST_CHECK( !resMock->isOn );
  resMock->TurnOn();
  BOOST_CHECK( resMock->isOn );
  resMock->TurnOff();
  BOOST_CHECK( !resMock->isOn );
}

BOOST_AUTO_TEST_SUITE_END()
