#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "signalstate.hpp"

// =====================

BOOST_AUTO_TEST_SUITE( SignalState )

BOOST_AUTO_TEST_CASE( ToString )
{
  Signalbox::SignalState s;
  std::string res;

  s = Signalbox::SignalState::Inactive;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Inactive" );
  
  s = Signalbox::SignalState::Done;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Done" );
  
  s = Signalbox::SignalState::Red;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Red" );
  
  s = Signalbox::SignalState::Yellow;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Yellow" );
  
  s = Signalbox::SignalState::DoubleYellow;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "DoubleYellow" );
  
  s = Signalbox::SignalState::Green;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Green" );
}

BOOST_AUTO_TEST_CASE( StreamInsertion )
{
  Signalbox::SignalState s;
  std::stringstream res;

  s = Signalbox::SignalState::Inactive;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Inactive" );
  res.str(std::string()); // Empty the stream
  
  s = Signalbox::SignalState::Done;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Done" );
  res.str(std::string());
  
  s = Signalbox::SignalState::Red;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Red" );
  res.str(std::string());
  
  s = Signalbox::SignalState::Yellow;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Yellow" );
  res.str(std::string());
  
  s = Signalbox::SignalState::DoubleYellow;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "DoubleYellow" );
  res.str(std::string());
  
  s = Signalbox::SignalState::Green;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Green" );
  res.str(std::string());
}

BOOST_AUTO_TEST_CASE( Parse )
{
  Signalbox::SignalState s;

  Signalbox::Parse( std::string("Done"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalState::Done );

  Signalbox::Parse( std::string("Inactive"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalState::Inactive );
  
  Signalbox::Parse( std::string("Red"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalState::Red );
  
  Signalbox::Parse( std::string("Yellow"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalState::Yellow );
  
  Signalbox::Parse( std::string("DoubleYellow"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalState::DoubleYellow );
  
  Signalbox::Parse( std::string("Green"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalState::Green );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  Signalbox::SignalState bad;

  std::string msg("Could not parse 'NoSuchVal' to SignalState");
  BOOST_CHECK_EXCEPTION( Signalbox::Parse( std::string("NoSuchVal"), bad ),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
