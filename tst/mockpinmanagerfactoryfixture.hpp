#pragma once

#include "mockpinmanagerfactory.hpp"

struct MockPinManagerFactoryFixture {
  Signalbox::MockPinManagerFactory mpmf;

  MockPinManagerFactoryFixture() : mpmf() {}
};
