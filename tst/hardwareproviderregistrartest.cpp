#include <boost/test/unit_test.hpp>

#include "mockpca9685.hpp"
#include "exceptionmessagecheck.hpp"

#include "hardwareproviderregistrar.hpp"

BOOST_AUTO_TEST_SUITE( HardwareProviderRegistrar )

BOOST_AUTO_TEST_SUITE( PWMChannelProvider )

BOOST_AUTO_TEST_CASE( RegisterAndFetch )
{
  Signalbox::HardwareProviderRegistrar hpr;

  const std::string name = "mymock";
  const unsigned int bus = 1;
  const unsigned int address = 0x40;
  Signalbox::MockPCA9685 device(name, bus, address);

  hpr.RegisterPWMChannelProvider( name, &device );

  auto fetched = hpr.GetPWMChannelProvider( name );

  BOOST_CHECK_EQUAL( fetched, &device );
}

BOOST_AUTO_TEST_CASE( NoPWMChannelProvider )
{
  Signalbox::HardwareProviderRegistrar hpr;
  
  std::string msg("PWMChannelProvider 'none' not found");

  // Check when empty
  BOOST_CHECK_EXCEPTION( hpr.GetPWMChannelProvider("none"),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );

  const std::string name = "mymock";
  const unsigned int bus = 1;
  const unsigned int address = 0x40;
  Signalbox::MockPCA9685 device(name, bus, address);

  hpr.RegisterPWMChannelProvider( name, &device );
  // Check that we still get exception on non-existent provider
  BOOST_CHECK_EXCEPTION( hpr.GetPWMChannelProvider("none"),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_CASE( NameUsedTwice )
{
  Signalbox::HardwareProviderRegistrar hpr;
  
  const std::string name = "mymock";
  const unsigned int bus = 1;
  const unsigned int address = 0x40;
  Signalbox::MockPCA9685 device1(name, bus, address);
  Signalbox::MockPCA9685 device2(name, bus, address+2);

  hpr.RegisterPWMChannelProvider( name, &device1 );

  std::string msg("PWMChannelProvider 'mymock' already registered");
  BOOST_CHECK_EXCEPTION( hpr.RegisterPWMChannelProvider( name, &device2 );,
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
