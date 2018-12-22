#pragma once

#include <map>
#include <string>
#include <memory>

#include "pinmanagerfactory.hpp"

namespace Signalbox {
  /*
    Use a trick to enable different output destinations to register
    themselves at runtime

    The selector for each destination is derived from this abstract
    class and calls AddSelector in its constructor to register itself
    into the static map 'selectors' held by this class.

    Each of those selectors also defines a static object of itself in
    its source file. The runtime will construct each of these before
    calling main, and the constructors will register them into the
    'selectors' map

    The main program can then query the static methods of this
    abstract base class to get information about the output
    destinations which are available
   */
  class OutputSelector {
  public:
    static std::string ListOutputSelectors();

    static OutputSelector* GetSelector( std::string name );
    
    virtual ~OutputSelector() {}

    virtual PinManagerFactory* GetPinManagerFactory() = 0;
  protected:
    void AddSelector(std::string name, OutputSelector* s) {
      OutputSelector::selectors[name] = s;
    }
  private:
    static std::map<std::string,OutputSelector*> selectors;
  };
}
