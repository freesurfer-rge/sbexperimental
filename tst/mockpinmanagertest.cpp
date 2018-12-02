#include <boost/test/unit_test.hpp>

#include "mockpinmanager.hpp"
#include "mockdigitaloutputpin.hpp"

#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE( MockPinManager )

BOOST_AUTO_TEST_CASE( CreateOutputPin )
{
  Signalbox::MockPinManager pm;

  const std::string pinId = "AnyId";

  auto dop = pm.CreateDigitalOutputPin(pinId);
  BOOST_REQUIRE( dop );

  auto mdop = dynamic_cast<Signalbox::MockDigitalOutputPin*>(dop);
  BOOST_CHECK( mdop );
  BOOST_CHECK_EQUAL( mdop->Get(), false );

  mdop->TurnOn();
  BOOST_CHECK_EQUAL( mdop->Get(), true );
  mdop->TurnOff();
  BOOST_CHECK_EQUAL( mdop->Get(), false);
}

BOOST_AUTO_TEST_CASE( CreateTwoOutputPins )
{
  Signalbox::MockPinManager pm;

  const std::string id1 = "Pin1";
  const std::string id2 = "Pin2";

  auto dop1 = pm.CreateDigitalOutputPin(id1);
  auto dop2 = pm.CreateDigitalOutputPin(id2);
  BOOST_REQUIRE( dop1 );
  BOOST_REQUIRE( dop2 );
  BOOST_REQUIRE_NE( dop1, dop2 );

  auto mdop1 = dynamic_cast<Signalbox::MockDigitalOutputPin*>(dop1);
  auto mdop2 = dynamic_cast<Signalbox::MockDigitalOutputPin*>(dop2);
  BOOST_REQUIRE( mdop1 );
  BOOST_REQUIRE( mdop2 );
  BOOST_REQUIRE_NE( mdop1, mdop2 );

  // Both should be off
  BOOST_CHECK( !mdop1->Get() );
  BOOST_CHECK( !mdop2->Get() );

  // Can switch one without affecting the other
  mdop2->TurnOn();
  BOOST_CHECK( !mdop1->Get() );
  BOOST_CHECK( mdop2->Get() );

  mdop1->TurnOn();
  BOOST_CHECK( mdop1->Get() );
  BOOST_CHECK( mdop2->Get() );

  mdop2->TurnOff();
  BOOST_CHECK( mdop1->Get() );
  BOOST_CHECK( !mdop2->Get() );
}

BOOST_AUTO_TEST_CASE( DuplicateCreateOutputPin )
{
  Signalbox::MockPinManager pm;

  const std::string pinId = "AnyId";

  auto dop = pm.CreateDigitalOutputPin(pinId);
  BOOST_REQUIRE( dop );

  std::string msg("Pin 'AnyId' already exists");
  BOOST_CHECK_EXCEPTION( pm.CreateDigitalOutputPin(pinId),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
