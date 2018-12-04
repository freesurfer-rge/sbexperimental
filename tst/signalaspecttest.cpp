#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "signalaspect.hpp"

// =====================

BOOST_AUTO_TEST_SUITE( SignalAspect )

BOOST_AUTO_TEST_CASE( ToString )
{
  Signalbox::SignalAspect s;
  std::string res;

  s = Signalbox::SignalAspect::Inactive;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Inactive" );
  
  s = Signalbox::SignalAspect::Done;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Done" );
  
  s = Signalbox::SignalAspect::Red;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Red" );
  
  s = Signalbox::SignalAspect::Yellow;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Yellow" );
  
  s = Signalbox::SignalAspect::DoubleYellow;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "DoubleYellow" );
  
  s = Signalbox::SignalAspect::Green;
  res = Signalbox::ToString( s );
  BOOST_CHECK_EQUAL( res, "Green" );
}

BOOST_AUTO_TEST_CASE( StreamInsertion )
{
  Signalbox::SignalAspect s;
  std::stringstream res;

  s = Signalbox::SignalAspect::Inactive;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Inactive" );
  res.str(std::string()); // Empty the stream
  
  s = Signalbox::SignalAspect::Done;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Done" );
  res.str(std::string());
  
  s = Signalbox::SignalAspect::Red;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Red" );
  res.str(std::string());
  
  s = Signalbox::SignalAspect::Yellow;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Yellow" );
  res.str(std::string());
  
  s = Signalbox::SignalAspect::DoubleYellow;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "DoubleYellow" );
  res.str(std::string());
  
  s = Signalbox::SignalAspect::Green;
  res << s;
  BOOST_CHECK_EQUAL( res.str(), "Green" );
  res.str(std::string());
}

BOOST_AUTO_TEST_CASE( Parse )
{
  Signalbox::SignalAspect s;

  Signalbox::Parse( std::string("Done"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalAspect::Done );

  Signalbox::Parse( std::string("Inactive"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalAspect::Inactive );
  
  Signalbox::Parse( std::string("Red"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalAspect::Red );
  
  Signalbox::Parse( std::string("Yellow"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalAspect::Yellow );
  
  Signalbox::Parse( std::string("DoubleYellow"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalAspect::DoubleYellow );
  
  Signalbox::Parse( std::string("Green"), s );
  BOOST_CHECK_EQUAL( s, Signalbox::SignalAspect::Green );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  Signalbox::SignalAspect bad;

  std::string msg("Could not parse 'NoSuchVal' to SignalAspect");
  BOOST_CHECK_EXCEPTION( Signalbox::Parse( std::string("NoSuchVal"), bad ),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
