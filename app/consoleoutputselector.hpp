#pragma once
#include "outputselector.hpp"

namespace Signalbox {
  class ConsoleOutputSelector : public OutputSelector {
  public:
    ConsoleOutputSelector() {
      this->AddSelector( std::string("console"), this );
    }

    virtual std::unique_ptr<PinManager> CreatePinManager() override;
  };
}
