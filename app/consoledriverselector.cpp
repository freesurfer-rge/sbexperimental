#include "consoledriver.hpp"
#include "consoledriverselector.hpp"

namespace Signalbox {
  static ConsoleDriverSelector cos;
  static ConsoleDriver cd;

  ControlledItemDriver* ConsoleDriverSelector::GetDriver() {
    return &cd;
  }
}
