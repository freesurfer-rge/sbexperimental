#include <iostream>
#include "outputselector.hpp"

namespace Signalbox {
  std::map<std::string,OutputSelector*> OutputSelector::selectors;

  std::string OutputSelector::chosen;
  
  std::string OutputSelector::ListOutputSelectors() {
    std::string res;

    if( OutputSelector::selectors.size() < 1 ) {
      throw std::runtime_error("No OutputSelectors found");
    }
    
    for( auto it=OutputSelector::selectors.begin();
	 it!=OutputSelector::selectors.end();
	 ++it ) {
      res += it->first;
      res += "|";
    }
    std::cout << __FUNCTION__ << " : " << res << std::endl;
    res.pop_back();

    return res;
  }

}
