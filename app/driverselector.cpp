#include "driverselector.hpp"

namespace Signalbox {
  std::map<std::string,DriverSelector*> DriverSelector::selectors;

  DriverSelector* DriverSelector::GetSelector( std::string name ) {
    return DriverSelector::selectors.at(name);
  }
  
  std::string DriverSelector::ListDriverSelectors() {
    std::string res;

    if( DriverSelector::selectors.size() < 1 ) {
      throw std::runtime_error("No DriverSelectors found");
    }
    
    for( auto it=DriverSelector::selectors.begin();
	 it!=DriverSelector::selectors.end();
	 ++it ) {
      res += it->first;
      res += "|";
    }
    res.pop_back();

    return res;
  }
}
