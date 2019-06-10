#pragma once

#include <memory>

#include <boost/test/unit_test.hpp>

#include "servoturnoutmotorfactory.hpp"
#include "mockpinmanager.hpp"
#include "servoturnoutmotordata.hpp"

struct MockServoTurnoutMotorFactoryFixture {
  Signalbox::MockPinManager mpm;
  Signalbox::ServoTurnoutMotorFactory shf;

  MockServoTurnoutMotorFactoryFixture() :
    mpm(),
    shf(&(this->mpm)) {}

  // Remove copy constructor and operator=
  MockServoTurnoutMotorFactoryFixture(MockServoTurnoutMotorFactoryFixture&) = delete;
  MockServoTurnoutMotorFactoryFixture& operator=(MockServoTurnoutMotorFactoryFixture&) = delete;

  // Helper function
  std::unique_ptr<Signalbox::ServoTurnoutMotor> CreateServoTurnoutMotor(const Signalbox::ServoTurnoutMotorData& sd) {
    std::unique_ptr<Signalbox::ControlledItem> ci;
    ci = this->shf.Manufacture(&sd);
    BOOST_REQUIRE(ci);

    // Note the following is dangerous if the dynamic_cast fails (returning NULL)
    // Since we know what we just created it should be fine, but in general
    // this is not a great thing to do
    return std::unique_ptr<Signalbox::ServoTurnoutMotor>(dynamic_cast<Signalbox::ServoTurnoutMotor*>(ci.release()));
  }
};
