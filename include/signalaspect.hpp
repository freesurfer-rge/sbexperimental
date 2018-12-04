#pragma once

#include <iostream>
#include <string>

namespace Signalbox {
  enum class SignalAspect { Inactive,
			    Done,
			    Red,
			    DoubleYellow,
			    Yellow,
			    Green
  };
  
  std::ostream& operator<<( std::ostream& os, const SignalAspect s );
  
  std::string ToString( const SignalAspect s );
  
  void Parse( const std::string str, SignalAspect& s );
}

