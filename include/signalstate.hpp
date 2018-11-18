#pragma once

#include <iostream>

namespace Signalbox {
  enum class SignalState { Inactive,
			   Done,
			   Red,
			   DoubleYellow,
			   Yellow,
			   Green
  };
  
  std::ostream& operator<<( std::ostream& os, const SignalState s );
}

