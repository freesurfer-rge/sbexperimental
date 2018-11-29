#pragma once
#include "outputselector.hpp"

namespace Signalbox {
  class ConsoleOutputSelector : public OutputSelector {
  public:
    ConsoleOutputSelector() {
      this->AddSelf();
    }
  protected:
    virtual void AddSelf() override;
  };
}
