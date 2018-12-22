#include <boost/test/unit_test.hpp>

#include "pigpiodpinmanager.hpp"

#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE( PiGPIOdPinMananger )

BOOST_AUTO_TEST_CASE( NoDoubleConstruct )
{
  Signalbox::PiGPIOdPinManager pm;

  std::string msg("PiGPIOdPinManager already exists");
  BOOST_CHECK_EXCEPTION( Signalbox::PiGPIOdPinManager(),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}

BOOST_AUTO_TEST_CASE( ConstructAfterDestruct )
{
  BOOST_CHECK_NO_THROW( Signalbox::PiGPIOdPinManager() );
  
  BOOST_CHECK_NO_THROW( Signalbox::PiGPIOdPinManager() );
}

BOOST_AUTO_TEST_CASE( ParseId )
{
  Signalbox::PiGPIOdPinManager pm;

  const std::string pinId = "GPIO02";

  auto res = pm.ParseId(pinId);

  BOOST_CHECK_EQUAL(2, res);
}

BOOST_AUTO_TEST_CASE( ParseIdFail )
{
  Signalbox::PiGPIOdPinManager pm;

  const std::string pinId = "GPIOnn";
  
  BOOST_CHECK_THROW( pm.ParseId(pinId), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( CreateOutputPin )
{
  Signalbox::PiGPIOdPinManager pm;

  const std::string pinId = "GPIO02";

  auto dop = pm.CreateDigitalOutputPin(pinId);
  BOOST_REQUIRE( dop );

  auto mdop = dynamic_cast<Signalbox::PiGPIOdDigitalOutputPin*>(dop);
  BOOST_CHECK( mdop );
  BOOST_CHECK_EQUAL( dop->Get(), false );

  dop->TurnOn();
  BOOST_CHECK_EQUAL( dop->Get(), true );
  dop->TurnOff();
  BOOST_CHECK_EQUAL( dop->Get(), false);
}

BOOST_AUTO_TEST_CASE( CreateTwoOutputPins )
{
  Signalbox::PiGPIOdPinManager pm;

  const std::string id1 = "GPIO02";
  const std::string id2 = "GPIO03";

  auto dop1 = pm.CreateDigitalOutputPin(id1);
  auto dop2 = pm.CreateDigitalOutputPin(id2);
  BOOST_REQUIRE( dop1 );
  BOOST_REQUIRE( dop2 );
  BOOST_REQUIRE_NE( dop1, dop2 );

  auto mdop1 = dynamic_cast<Signalbox::PiGPIOdDigitalOutputPin*>(dop1);
  auto mdop2 = dynamic_cast<Signalbox::PiGPIOdDigitalOutputPin*>(dop2);
  BOOST_REQUIRE( mdop1 );
  BOOST_REQUIRE( mdop2 );
  BOOST_REQUIRE_NE( mdop1, mdop2 );

  // Both should be off
  BOOST_CHECK( !dop1->Get() );
  BOOST_CHECK( !dop2->Get() );

  // Can switch one without affecting the other
  dop2->TurnOn();
  BOOST_CHECK( !dop1->Get() );
  BOOST_CHECK( dop2->Get() );

  mdop1->TurnOn();
  BOOST_CHECK( dop1->Get() );
  BOOST_CHECK( dop2->Get() );

  dop2->TurnOff();
  BOOST_CHECK( dop1->Get() );
  BOOST_CHECK( !dop2->Get() );
}

BOOST_AUTO_TEST_CASE( DuplicateCreateOutputPin )
{
  Signalbox::PiGPIOdPinManager pm;

  const std::string pinId = "GPIO02";

  auto dop = pm.CreateDigitalOutputPin(pinId);
  BOOST_REQUIRE( dop );

  std::string msg("Pin 'GPIO02' already exists");
  BOOST_CHECK_EXCEPTION( pm.CreateDigitalOutputPin(pinId),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
