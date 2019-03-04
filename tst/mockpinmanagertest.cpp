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

  std::string msg("Pin 'AnyId' already exists as OutputPin");
  BOOST_CHECK_EXCEPTION( pm.CreateDigitalOutputPin(pinId),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}

BOOST_AUTO_TEST_CASE( CreateInputPin )
{
  Signalbox::MockPinManager pm;

  Signalbox::DigitalInputPinData data;
  data.id = "AnyId";
  data.settings["First"] = "0";
  data.settings["Second"] = "12";

  auto dip = pm.CreateDigitalInputPin(data);
  BOOST_REQUIRE( dip );

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE( mdip );
  BOOST_CHECK_EQUAL( mdip->id, data.id );
  BOOST_CHECK_EQUAL( mdip->Get(), false );
  BOOST_REQUIRE_EQUAL( mdip->createSettings.size(), 2 );
  BOOST_CHECK_EQUAL( mdip->createSettings.at("First"), "0" );
  BOOST_CHECK_EQUAL( mdip->createSettings.at("Second"), "12" );
}

BOOST_AUTO_TEST_CASE( CreateTwoInputPins )
{
  Signalbox::MockPinManager pm;

  Signalbox::DigitalInputPinData data1, data2;
  data1.id = "GPIO1";
  data2.id = "GPIO2";
  data1.settings["OneSetting"] = "OneValue";

  auto dip1 = pm.CreateDigitalInputPin(data1);
  auto dip2 = pm.CreateDigitalInputPin(data2);
  BOOST_REQUIRE( dip1 );
  BOOST_REQUIRE( dip1 );
  BOOST_REQUIRE_NE( dip1, dip2 );

  auto mdip1 = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip1);
  auto mdip2 = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip2);
  BOOST_REQUIRE( mdip1 );
  BOOST_REQUIRE( mdip2 );
  BOOST_CHECK_NE( mdip1, mdip2 );
  BOOST_CHECK_EQUAL( mdip1->Get(), false );
  BOOST_CHECK_EQUAL( mdip2->Get(), false );

  BOOST_CHECK_EQUAL( mdip1->id, "GPIO1" );
  BOOST_CHECK_EQUAL( mdip2->id, "GPIO2" );
  
  BOOST_REQUIRE_EQUAL( mdip1->createSettings.size(), 1 );
  BOOST_CHECK_EQUAL( mdip1->createSettings.at("OneSetting"), "OneValue" );
  BOOST_CHECK_EQUAL( mdip2->createSettings.size(), 0 );
}

BOOST_AUTO_TEST_CASE( DuplicateCreateInputPin )
{
  Signalbox::MockPinManager pm;

  Signalbox::DigitalInputPinData data1, data2;
  data1.id = "AnyId";
  data2.id = "AnyId";
  data1.settings["OneSetting"] = "OneValue";

  auto dip = pm.CreateDigitalInputPin(data1);
  BOOST_REQUIRE( dip );

  std::string msg("Pin 'AnyId' already exists as InputPin");
  BOOST_CHECK_EXCEPTION( pm.CreateDigitalInputPin(data2),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
