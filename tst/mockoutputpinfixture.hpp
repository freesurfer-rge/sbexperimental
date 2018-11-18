#pragma once

#include "mockoutputpin.hpp"

struct MockOutputPinFixture {
  MockOutputPinFixture() {
    Signalbox::OutputPin::sample = std::unique_ptr<Signalbox::OutputPin>(new Signalbox::MockOutputPin());
  }
  
  ~MockOutputPinFixture() {
    Signalbox::MockOutputPin::allPins.clear();
  }
};
