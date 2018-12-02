#pragma once

#include "mockpinmanager.hpp"

struct MockPinManagerFixture {
  Signalbox::MockPinManager mpm;
  Signalbox::PinManager *pm;

  MockPinManagerFixture() :
    mpm(),
    pm() {
    this->pm = &(this->mpm);
  }

  // Delete copy constructor and operator=
  // This removes a compiler warning due to the pointer member
  MockPinManagerFixture(MockPinManagerFixture&) = delete;
  MockPinManagerFixture& operator=(MockPinManagerFixture&) = delete;
};
