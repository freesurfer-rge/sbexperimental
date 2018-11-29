#include "outputselector.hpp"

namespace Signalbox {
  std::map<std::string,OutputSelector*> OutputSelector::selectors;

  std::set<std::string> OutputSelector::ListOutputSelectors() {
    std::set<std::string> res;

    for( auto it= OutputSelector::selectors.begin();
	 it != OutputSelector::selectors.end();
	 ++it ) {
      res.insert(it->first);
    }

    return res;
  }

}
