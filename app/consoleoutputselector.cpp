#include "consolepinmanager.hpp"
#include "consoleoutputselector.hpp"

namespace Signalbox {
  static ConsoleOutputSelector cos;

  std::unique_ptr<PinManager> ConsoleOutputSelector::CreatePinManager() {
    return std::unique_ptr<Signalbox::PinManager>(new Signalbox::ConsolePinManager() );
  }
}
