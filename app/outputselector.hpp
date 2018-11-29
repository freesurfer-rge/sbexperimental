#pragma once

#include <map>
#include <string>

namespace Signalbox {
  class OutputSelector {
  public:
    static std::string ListOutputSelectors();

    static std::string chosen;
    
    virtual ~OutputSelector() {}
  protected:
    void AddSelector(std::string name, OutputSelector* s ) {
      OutputSelector::selectors[name] = s;
    }

    virtual void AddSelf() = 0;
  private:
    static std::map<std::string,OutputSelector*> selectors;
  };
}
