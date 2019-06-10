#pragma once

#include <iostream>
#include <string>

namespace Signalbox {
  enum class TurnoutState { Straight,
			    Curved
  };

  std::ostream& operator<<( std::ostream& os, const TurnoutState s );
  
  std::string ToString( const TurnoutState s );
  
  void Parse( const std::string str, TurnoutState& s );
}
