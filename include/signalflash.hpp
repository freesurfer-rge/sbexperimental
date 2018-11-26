#pragma once

#include <iostream>
#include <string>

namespace Signalbox {
  enum class SignalFlash { Steady,
			   Flashing
  };

  std::ostream& operator<<( std::ostream& os, const SignalFlash f );

  std::string ToString( const SignalFlash f );
  
  void Parse( const std::string str, SignalFlash& f );

}
