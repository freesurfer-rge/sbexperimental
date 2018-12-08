#include <boost/test/unit_test.hpp>

#include "mockpinmanager.hpp"
#include "controlleditemmanager.hpp"

#include "signalheaddata.hpp"

BOOST_AUTO_TEST_SUITE( SignalHeadData )

BOOST_AUTO_TEST_SUITE( GetErrors )

BOOST_AUTO_TEST_CASE( InvalidId )
{
  Signalbox::SignalHeadData sd;

  sd.aspectCount = 2; // Make this valid
  auto res = sd.GetErrors();

  BOOST_REQUIRE_EQUAL( res.size(), 1 );

  const std::string expected("Invalid id");
  BOOST_CHECK_EQUAL( res[0].message, expected );
}

BOOST_AUTO_TEST_CASE( AspectCountTooLow )
{
  Signalbox::SignalHeadData sd;
  const std::string expected("Invalid aspectCount");
  
  sd.id = Signalbox::ItemId(1);
  
  sd.aspectCount = 1;
  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  BOOST_CHECK_EQUAL( res.at(0).message, expected ); 
}

BOOST_AUTO_TEST_CASE( AspectCountTooHigh )
{
  Signalbox::SignalHeadData sd;
  const std::string expected("Invalid aspectCount");
  
  sd.id = Signalbox::ItemId(1);
  
  sd.aspectCount = 5;
  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  BOOST_CHECK_EQUAL( res.at(0).message, expected ); 
}

BOOST_AUTO_TEST_CASE( NoRedAspect )
{
  Signalbox::SignalHeadData sd;

  sd.id = Signalbox::ItemId::Random();
  sd.aspectCount = 2;

  sd.pinData[Signalbox::SignalHeadPins::Green] = "0";

  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  const std::string expected("No Red aspect");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_CASE( NoGreenAspect )
{
  Signalbox::SignalHeadData sd;

  sd.id = Signalbox::ItemId::Random();
  sd.aspectCount = 2;

  sd.pinData[Signalbox::SignalHeadPins::Red] = "0";

  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  const std::string expected("No Green aspect");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_CASE( InvalidYellow1Aspect )
{
  Signalbox::SignalHeadData sd;

  sd.id = Signalbox::ItemId::Random();
  sd.aspectCount = 2;

  sd.pinData[Signalbox::SignalHeadPins::Red] = "0";
  sd.pinData[Signalbox::SignalHeadPins::Green] = "1";
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = "2";
  
  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  const std::string expected("Yellow1 aspect not allowed");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_CASE( MissingYellow1Aspect )
{
  Signalbox::SignalHeadData sd;

  sd.id = Signalbox::ItemId::Random();
  sd.aspectCount = 3;

  sd.pinData[Signalbox::SignalHeadPins::Red] = "0";
  sd.pinData[Signalbox::SignalHeadPins::Green] = "1";
  
  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  const std::string expected("No Yellow1 aspect");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_CASE( InvalidYellow2Aspect )
{
  Signalbox::SignalHeadData sd;

  sd.id = Signalbox::ItemId::Random();
  sd.aspectCount = 3;

  sd.pinData[Signalbox::SignalHeadPins::Red] = "0";
  sd.pinData[Signalbox::SignalHeadPins::Green] = "1";
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = "2";
  sd.pinData[Signalbox::SignalHeadPins::Yellow2] = "3";
  
  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  const std::string expected("Yellow2 aspect not allowed");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_CASE( MissingYellow2Aspect )
{
  Signalbox::SignalHeadData sd;

  sd.id = Signalbox::ItemId::Random();
  sd.aspectCount = 4;

  sd.pinData[Signalbox::SignalHeadPins::Red] = "0";
  sd.pinData[Signalbox::SignalHeadPins::Green] = "1";
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = "2";
  
  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  const std::string expected("No Yellow2 aspect");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_CASE( DuplicatePins )
{
  Signalbox::SignalHeadData sd;

  sd.id = Signalbox::ItemId::Random();
  sd.aspectCount = 2;

  sd.pinData[Signalbox::SignalHeadPins::Red] = "0";
  sd.pinData[Signalbox::SignalHeadPins::Green] = "0";

  auto res = sd.GetErrors();

  BOOST_CHECK_EQUAL( res.size(), 1 );
  const std::string expected("Duplicate pin values present");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_CASE( GetFactory )
{
  Signalbox::SignalHeadData sd;

  Signalbox::MockPinManager mpm;
  Signalbox::ControlledItemManager cim(&mpm);

  auto cif = sd.GetFactory(&cim);
  BOOST_REQUIRE(cif);
  auto shf = dynamic_cast<Signalbox::SignalHeadFactory*>(cif);
  BOOST_REQUIRE(shf);
}

BOOST_AUTO_TEST_SUITE_END()
