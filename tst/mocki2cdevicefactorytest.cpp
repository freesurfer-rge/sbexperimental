#include <boost/test/unit_test.hpp>

#include "mockpca9685.hpp"
#include "exceptionmessagecheck.hpp"

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
  Signalbox::MockI2CDeviceFactory df;
  
  Signalbox::I2CDeviceData deviceData;
  deviceData.kind = "noSuchKind";
  deviceData.bus = 0;
  deviceData.address = 0x40;
  deviceData.name = "SC01";

  std::string msg("Specified device kind 'noSuchKind' not recognised");
  BOOST_CHECK_EXCEPTION( df.CreateDevice(deviceData),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_CASE( CreateDuplicateName )
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

  Signalbox::I2CDeviceData deviceData2;
  deviceData2.kind = "pca9685";
  deviceData2.bus = 1;
  deviceData2.address = 0x40;
  deviceData2.name = "SC01";
  deviceData2.settings["referenceClock"] = "25e6";
  deviceData2.settings["pwmFrequency"] = "50";

  std::string msg("Specified device name 'SC01' already exists");
  BOOST_CHECK_EXCEPTION( df.CreateDevice(deviceData2),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_CASE( CreateDuplicateBusAndAddress )
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

  Signalbox::I2CDeviceData deviceData2;
  deviceData2.kind = "pca9685";
  deviceData2.bus = 0;
  deviceData2.address = 0x40;
  deviceData2.name = "SC02";
  deviceData2.settings["referenceClock"] = "25e6";
  deviceData2.settings["pwmFrequency"] = "50";

  std::string msg("Specified bus and address [0, 0x40] already assigned to a device");
  BOOST_CHECK_EXCEPTION( df.CreateDevice(deviceData2),
			 std::out_of_range,
			 GetExceptionMessageChecker<std::out_of_range>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
