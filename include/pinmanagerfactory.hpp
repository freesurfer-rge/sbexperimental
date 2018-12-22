#pragma once

#include <memory>

#include "pinmanager.hpp"

namespace Signalbox {
  class PinManagerFactory {
  public:
    virtual ~PinManagerFactory() {}

    virtual std::unique_ptr<PinManager> Create() = 0;
  };
}
