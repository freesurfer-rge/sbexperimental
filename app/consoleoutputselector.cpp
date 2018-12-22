#include "consolepinmanager.hpp"
#include "consoleoutputselector.hpp"

namespace Signalbox {
  static ConsoleOutputSelector cos;

  PinManagerFactory* ConsoleOutputSelector::GetPinManagerFactory() {
    return &(this->cpmf);
  }
}
