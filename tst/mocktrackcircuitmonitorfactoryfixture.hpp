#pragma once

#include <memory>

#include <boost/test/unit_test.hpp>

#include "trackcircuitmonitor.hpp"
#include "trackcircuitmonitordata.hpp"
#include "trackcircuitmonitorfactory.hpp"
#include "mockpinmanager.hpp"
#include "mockrailtrafficcontrolclient.hpp"

struct MockTrackCircuitMonitorFactoryFixture {
  Signalbox::MockPinManager mpm;
  Signalbox::MockRailTrafficControlClient rtc;
  Signalbox::TrackCircuitMonitorFactory tcmf;

  MockTrackCircuitMonitorFactoryFixture() :
    mpm(),
    rtc(),
    tcmf(&(this->mpm), &(this->rtc)) {
    this->rtc.host = "mock.local";
    this->rtc.port = 1044;
  }

  // Remove copy constructor and operator=
  MockTrackCircuitMonitorFactoryFixture(MockTrackCircuitMonitorFactoryFixture&) = delete;
  MockTrackCircuitMonitorFactoryFixture& operator=(MockTrackCircuitMonitorFactoryFixture&) = delete;

  // Helper
  std::unique_ptr<Signalbox::TrackCircuitMonitor> CreateTrackCircuitMonitor(const Signalbox::TrackCircuitMonitorData& tcmd) {
    std::unique_ptr<Signalbox::ControlledItem> ci;
    ci = this->tcmf.Manufacture(&tcmd);
    BOOST_REQUIRE(ci);

    // Note the following is dangerous if the dynamic_cast fails (returning NULL)
    // Since we know what we just created it should be fine, but in general
    // this is not a great thing to do
    return std::unique_ptr<Signalbox::TrackCircuitMonitor>(dynamic_cast<Signalbox::TrackCircuitMonitor*>(ci.release()));
  }

};
