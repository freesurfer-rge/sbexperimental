#include <sstream>

#include "rtcselector.hpp"

namespace Signalbox {
  std::map<std::string,RTCSelector*> RTCSelector::selectors;

  RTCSelector* RTCSelector::GetSelector( std::string name ) {
    if( RTCSelector::selectors.count(name) != 1 ) {
      std::stringstream msg;
      msg << "RTC selection "
	  << name
	  << " not recognised"
	  << std::endl;
      throw std::range_error(msg.str());
    }
    return RTCSelector::selectors.at(name);
  }

  std::string RTCSelector::ListRTCSelectors() {
    std::string res;

    if( RTCSelector::selectors.size() < 1 ) {
      throw std::runtime_error("No RTCSelectors found");
    }
    
    for( auto it=RTCSelector::selectors.begin();
	 it!=RTCSelector::selectors.end();
	 ++it ) {
      res += it->first;
      res += "|";
    }
    res.pop_back();

    return res;
  }
}
