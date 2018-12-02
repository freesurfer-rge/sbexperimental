#include <stdexcept>

#include "outputpin.hpp"

namespace Signalbox {
  std::unique_ptr<OutputPin> OutputPin::create(const std::string pinId) {
    if( !OutputPin::sample ) {
      throw std::runtime_error("OutputPin::sample is not set");
    }

    return OutputPin::sample->manufacture(pinId);
  }

  // Define the static sample member
  std::unique_ptr<OutputPin> OutputPin::sample;
}
