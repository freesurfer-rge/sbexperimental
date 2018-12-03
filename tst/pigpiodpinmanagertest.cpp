#include <boost/test/unit_test.hpp>

#include "pigpiodpinmanager.hpp"

BOOST_AUTO_TEST_SUITE( PiGPIOdPinMananger )

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

BOOST_AUTO_TEST_SUITE_END()
