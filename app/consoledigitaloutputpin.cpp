#include <iostream>
#include <sstream>

#include "consoledigitaloutputpin.hpp"

namespace Signalbox {
  void ConsoleDigitalOutputPin::Set(const bool value) {
    if( value ) {
      std::cout << "Pin : " << this->id << " ON" << std::endl;
    } else {
      std::cout << "Pin : " << this->id << " OFF" << std::endl;
    }
  }
  
  bool ConsoleDigitalOutputPin::Get() const {
    std::stringstream msg;
    msg << __PRETTY_FUNCTION__ << ": Not implemented";
    throw std::runtime_error(msg.str());
  }
}
