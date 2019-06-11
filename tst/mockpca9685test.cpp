#include <boost/test/unit_test.hpp>

#include "mockpca9685.hpp"

BOOST_AUTO_TEST_SUITE( MockPCA9685 )

BOOST_AUTO_TEST_CASE( ConstructorAndInitialise )
{
  const std::string name = "mymock";
  const unsigned int bus = 1;
  const unsigned int address = 0x40;
  Signalbox::MockPCA9685 device(name, bus, address);

  BOOST_CHECK_EQUAL( name, device.name );
  BOOST_CHECK_EQUAL( bus, device.i2cBus );
  BOOST_CHECK_EQUAL( address, device.i2cAddress );

  std::map<std::string,std::string> settings;
  settings["referenceClock"] = "25e6";
  settings["pwmFrequency"] = "50";

  device.Initialise(settings);

  BOOST_CHECK_EQUAL( 25e6, device.referenceClock );
  BOOST_CHECK_EQUAL( 50, device.pwmFrequency );
}

BOOST_AUTO_TEST_SUITE_END()
