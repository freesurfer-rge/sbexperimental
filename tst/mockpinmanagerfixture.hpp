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
};
