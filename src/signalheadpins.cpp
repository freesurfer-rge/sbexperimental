#include "signalheadpins.hpp"

#include <map>

namespace Signalbox {
  static std::map<std::string,SignalHeadPins> mapper {
						  std::make_pair("Red",SignalHeadPins::Red),
						  std::make_pair("Yellow1",SignalHeadPins::Yellow1),
						  std::make_pair("Yellow2",SignalHeadPins::Yellow2),
						  std::make_pair("Green",SignalHeadPins::Green)
  };

  SignalHeadPins StringToSignalHeadPins( const std::string str ) {
    auto it = mapper.find( str );
    if( it != mapper.end() ) {
      return it->second;
    }

    throw std::range_error("Unrecognised SignalHeadPins: " + str);
  }
}
