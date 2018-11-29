#pragma once

#include <map>
#include <string>
#include <memory>

#include "outputpin.hpp"

namespace Signalbox {
  class OutputSelector {
  public:
    static std::string ListOutputSelectors();

    static OutputSelector* GetSelector( std::string name );
    
    virtual ~OutputSelector() {}

    virtual std::unique_ptr<OutputPin> GetSample() = 0;
  protected:
    void AddSelector(std::string name, OutputSelector* s ) {
      OutputSelector::selectors[name] = s;
    }
  private:
    static std::map<std::string,OutputSelector*> selectors;
  };
}
