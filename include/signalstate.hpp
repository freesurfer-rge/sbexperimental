#pragma once

#include <iostream>
#include <string>

namespace Signalbox {
  enum class SignalState { Inactive,
			   Done,
			   Red,
			   DoubleYellow,
			   Yellow,
			   Green
  };
  
  std::ostream& operator<<( std::ostream& os, const SignalState s );

  std::string ToString( const SignalState s );
  
  void Parse( const std::string str, SignalState& s );
}

