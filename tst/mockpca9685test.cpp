#include <boost/test/unit_test.hpp>

#include "hardwareproviderregistrar.hpp"

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
  BOOST_CHECK_EQUAL( 0, device.assignedChannels.size() );
}

BOOST_AUTO_TEST_CASE( GetPWMChannel )
{
  const std::string name = "mymock";
  const unsigned int bus = 1;
  const unsigned int address = 0x40;
  Signalbox::MockPCA9685 device(name, bus, address);
  
  std::map<std::string,std::string> settings;
  settings["referenceClock"] = "25e6";
  settings["pwmFrequency"] = "50";

  device.Initialise(settings);

  // Now the actual work
  const std::string pwmChannelId = "00";
  std::map<std::string,std::string> pwmSettings;

  auto pwmChannel = device.GetPWMChannel(pwmChannelId, pwmSettings);
  BOOST_REQUIRE(pwmChannel);

  auto mpc = dynamic_cast<Signalbox::MockPWMChannel*>(pwmChannel);
  BOOST_REQUIRE(mpc);

  BOOST_CHECK_EQUAL( 1, device.assignedChannels.size() );
  BOOST_CHECK_EQUAL( 1, device.assignedChannels.count(0) );
  BOOST_CHECK_EQUAL( device.assignedChannels.at(0).get(), mpc );

  BOOST_CHECK_EQUAL( mpc->controller, name );
  BOOST_CHECK_EQUAL( mpc->controllerData, pwmChannelId );
}

BOOST_AUTO_TEST_CASE( RegisterWithRegistrar )
{
  const std::string name = "mymock";
  const unsigned int bus = 1;
  const unsigned int address = 0x40;
  Signalbox::MockPCA9685 device(name, bus, address);

  Signalbox::HardwareProviderRegistrar hpr;

  device.Register(&hpr);

  auto pcp = hpr.GetPWMChannelProvider(name);
  BOOST_CHECK_EQUAL( pcp, &device );
}

BOOST_AUTO_TEST_SUITE_END()
