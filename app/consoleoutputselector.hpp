#pragma once
#include "outputselector.hpp"

#include "consolepinmanagerfactory.hpp"

namespace Signalbox {
  class ConsoleOutputSelector : public OutputSelector {
  public:
    ConsoleOutputSelector() :
      cpmf() {
      this->AddSelector( std::string("console"), this );
    }

    virtual PinManagerFactory* GetPinManagerFactory() override;

  private:
    ConsolePinManagerFactory cpmf;
  };
}
