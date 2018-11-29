#include "consoleoutputselector.hpp"

namespace Signalbox {
  static ConsoleOutputSelector cos;

  void ConsoleOutputSelector::AddSelf() {
    this->AddSelector( std::string("console"), this );
  }
}
