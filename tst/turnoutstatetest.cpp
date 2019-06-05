#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "turnoutstate.hpp"

BOOST_AUTO_TEST_SUITE( TurnoutState )

BOOST_AUTO_TEST_CASE( ToString )
{
  Signalbox::TurnoutState ts;
  std::string res;

  ts = Signalbox::TurnoutState::Straight;
  res = Signalbox::ToString( ts );
  BOOST_CHECK_EQUAL(res, "Straight");

  ts = Signalbox::TurnoutState::Curved;
  res = Signalbox::ToString( ts );
  BOOST_CHECK_EQUAL( res, "Curved" );
}

BOOST_AUTO_TEST_CASE( StreamInsertion )
{
  Signalbox::TurnoutState ts;
  std::stringstream res;

  ts = Signalbox::TurnoutState::Straight;
  res << ts;
  BOOST_CHECK_EQUAL( res.str(), "Straight" );
  res.str(std::string()); // Empty the stream

  ts = Signalbox::TurnoutState::Curved;
  res << ts;
  BOOST_CHECK_EQUAL( res.str(), "Curved" );
  res.str(std::string());
}

BOOST_AUTO_TEST_CASE( Parse )
{
  Signalbox::TurnoutState ts;

  Signalbox::Parse( std::string("Straight"), ts );
  BOOST_CHECK_EQUAL( ts, Signalbox::TurnoutState::Straight );

  Signalbox::Parse( std::string("Curved"), ts );
  BOOST_CHECK_EQUAL( ts, Signalbox::TurnoutState::Curved );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  Signalbox::TurnoutState bad;

  std::string msg("Could not parse 'NoSuchVal' to TurnoutState");
  BOOST_CHECK_EXCEPTION( Signalbox::Parse( std::string("NoSuchVal"), bad ),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
