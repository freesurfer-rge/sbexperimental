#pragma once

#include <string>

namespace Signalbox {
  enum class SignalHeadPins { Red,
			      Yellow1,
			      Yellow2,
			      Green
  };

  SignalHeadPins StringToSignalHeadPins( const std::string str );
}
