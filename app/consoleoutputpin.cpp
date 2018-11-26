#include <iostream>

#include "consoleoutputpin.hpp"

namespace Signalbox {
  void ConsoleOutputPin::TurnOn() {
    // Cast so a number is output (not the corresponding character)
    std::cout << "Pin : " << static_cast<int>(this->pin) << " ON" << std::endl;
  }
  
  void ConsoleOutputPin::TurnOff() {
    // Cast so a number is output (not the corresponding character)
    std::cout << "Pin : " << static_cast<int>(this->pin) << " OFF" << std::endl;
  }

  std::unique_ptr<OutputPin> ConsoleOutputPin::manufacture(const char pinId) {
    auto res = std::unique_ptr<ConsoleOutputPin>(new ConsoleOutputPin());
    res->pin = pinId;

    return std::unique_ptr<OutputPin>(res.release());
  }
}
