#include <iostream>

#include "consoleoutputpin.hpp"

namespace Signalbox {
  void ConsoleOutputPin::TurnOn() {
    std::cout << "Pin : " << this->pin << " ON" << std::endl;
  }
  
  void ConsoleOutputPin::TurnOff() {
    std::cout << "Pin : " << this->pin << " OFF" << std::endl;
  }

  std::unique_ptr<OutputPin> ConsoleOutputPin::manufacture(const char pinId) {
    auto res = std::unique_ptr<ConsoleOutputPin>(new ConsoleOutputPin());
    res->pin = pinId;

    return std::unique_ptr<OutputPin>(res.release());
  }
}
