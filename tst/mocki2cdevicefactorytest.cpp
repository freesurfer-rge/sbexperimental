#include <boost/test/unit_test.hpp>

#include "mockpca9685.hpp"

#include "mocki2cdevicefactory.hpp"

BOOST_AUTO_TEST_SUITE( MockI2CDeviceFactory )

BOOST_AUTO_TEST_CASE( CreateMockPCA9685 )
{
  Signalbox::MockI2CDeviceFactory df;
  
  Signalbox::I2CDeviceData deviceData;
  deviceData.kind = "pca9685";
  deviceData.bus = 0;
  deviceData.address = 0x40;
  deviceData.name = "SC01";
  deviceData.settings["referenceClock"] = "25e6";
  deviceData.settings["pwmFrequency"] = "50";

  auto device = df.CreateDevice(deviceData);
  BOOST_REQUIRE(device);

  BOOST_CHECK_EQUAL( deviceData.name, device->name );
  BOOST_CHECK_EQUAL( deviceData.bus, device->i2cBus );
  BOOST_CHECK_EQUAL( deviceData.address, device->i2cAddress );

  auto mockpca9685 = dynamic_cast<Signalbox::MockPCA9685*>(device.get());
  BOOST_REQUIRE(mockpca9685);

  BOOST_CHECK_EQUAL( 25e6, mockpca9685->referenceClock );
  BOOST_CHECK_EQUAL( 50, mockpca9685->pwmFrequency );
}

BOOST_AUTO_TEST_CASE( CreateUnknownDevice )
{
  BOOST_FAIL("Test not implemented");
}

BOOST_AUTO_TEST_CASE( CreateDuplicateName )
{
  BOOST_FAIL("Test not implemented");
}

BOOST_AUTO_TEST_CASE( CreateDuplicateBusAndAddress )
{
  BOOST_FAIL("Test not implemented");
}

BOOST_AUTO_TEST_SUITE_END()
