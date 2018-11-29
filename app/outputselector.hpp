#pragma once

#include <map>
#include <set>
#include <string>

namespace Signalbox {
  class OutputSelector {
  public:
    static std::set<std::string> ListOutputSelectors();
  protected:
    void AddSelector(std::string name, OutputSelector* s ) {
      OutputSelector::selectors[name] = s;
    }
  private:
    static std::map<std::string,OutputSelector*> selectors;
  };
}
