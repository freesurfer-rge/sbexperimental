#pragma once

#include <memory>

#include <boost/test/unit_test.hpp>

#include "signalheadfactory.hpp"
#include "mockpinmanager.hpp"

struct MockSignalHeadFactoryFixture {
  Signalbox::MockPinManager mpm;
  Signalbox::SignalHeadFactory shf;

  MockSignalHeadFactoryFixture() :
    mpm(),
    shf(&(this->mpm)) {}

  // Remove copy constructor and operator=
  MockSignalHeadFactoryFixture(MockSignalHeadFactoryFixture&) = delete;
  MockSignalHeadFactoryFixture& operator=(MockSignalHeadFactoryFixture&) = delete;

  // Helper function
  std::unique_ptr<Signalbox::SignalHead> CreateSignal(const Signalbox::SignalHeadData& sd) {
    std::unique_ptr<Signalbox::ControlledItem> ci;
    ci = this->shf.Manufacture(&sd);
    BOOST_REQUIRE(ci);

    // Note the following is dangerous if the dynamic_cast fails (returning NULL)
    // Since we know what we just created it should be fine, but in general
    // this is not a great thing to do
    return std::unique_ptr<Signalbox::SignalHead>(dynamic_cast<Signalbox::SignalHead*>(ci.release()));
  }
};
