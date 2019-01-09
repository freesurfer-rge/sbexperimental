#include <iostream>

#include "consoledigitalinputpin.hpp"

namespace Signalbox {
  bool ConsoleDigitalInputPin::Get() const {
    return this->state;
  }

  void ConsoleDigitalInputPin::Set(const bool level) {
    if( level ) {
      std::cout << "Input Pin : " << this->id << " ON" << std::endl;
    } else {
      std::cout << "Input Pin : " << this->id << " OFF" << std::endl;
    }
    this->state = level;
    this->NotifyOneUpdate();
  }
}
