#include "consoleoutputpin.hpp"
#include "consoleoutputselector.hpp"

namespace Signalbox {
  static ConsoleOutputSelector cos;

  std::unique_ptr<OutputPin> ConsoleOutputSelector::GetSample() {
    return std::unique_ptr<Signalbox::OutputPin>(new Signalbox::ConsoleOutputPin() );
  }
}
