#include <boost/test/unit_test.hpp>

#include "configuration/xercesguard.hpp"

BOOST_AUTO_TEST_SUITE( XercesGuard )

BOOST_AUTO_TEST_CASE( ConstructAndDestruct )
{
  Signalbox::Configuration::XercesGuard g;
  BOOST_CHECK( (&g) != nullptr );
  BOOST_TEST_CHECKPOINT("Constructed");
}

BOOST_AUTO_TEST_SUITE_END()
