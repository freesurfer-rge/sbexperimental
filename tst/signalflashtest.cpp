#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "signalflash.hpp"

BOOST_AUTO_TEST_SUITE( SignalFlash )

BOOST_AUTO_TEST_CASE( ToString )
{
  Signalbox::SignalFlash f;
  std::string res;

  f = Signalbox::SignalFlash::Steady;
  res = Signalbox::ToString( f );
  BOOST_CHECK_EQUAL( res, "Steady" );

  f = Signalbox::SignalFlash::Flashing;
  res = Signalbox::ToString( f );
  BOOST_CHECK_EQUAL( res, "Flashing" );
}

BOOST_AUTO_TEST_CASE( StreamInsertion )
{
  Signalbox::SignalFlash f;
  std::stringstream res;

  f = Signalbox::SignalFlash::Steady;
  res << f;
  BOOST_CHECK_EQUAL( res.str(), "Steady" );
  res.str(std::string()); // Empty the stream
  
  f = Signalbox::SignalFlash::Flashing;
  res << f;
  BOOST_CHECK_EQUAL( res.str(), "Flashing" );
  res.str(std::string());
}

BOOST_AUTO_TEST_CASE( Parse )
{
  Signalbox::SignalFlash f;

  Signalbox::Parse( std::string("Steady"), f );
  BOOST_CHECK_EQUAL( f, Signalbox::SignalFlash::Steady );

  Signalbox::Parse( std::string("Flashing"), f );
  BOOST_CHECK_EQUAL( f, Signalbox::SignalFlash::Flashing );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  Signalbox::SignalFlash bad;

  std::string msg("Could not parse 'NoSuchVal' to SignalFlash");
  BOOST_CHECK_EXCEPTION( Signalbox::Parse( std::string("NoSuchVal"), bad ),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
