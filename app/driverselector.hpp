#pragma once

#include <map>
#include <string>

#include "controlleditemdriver.hpp"

namespace Signalbox {
  class DriverSelector {
  public:
    static std::string ListDriverSelectors();

    static DriverSelector* GetSelector( std::string name );

    virtual ControlledItemDriver* GetDriver() = 0;

    virtual ~DriverSelector() {}
  protected:
    void AddSelector( std::string name, DriverSelector* s ) {
      DriverSelector::selectors[name] = s;
    }
  private:
    static std::map<std::string,DriverSelector*> selectors;
  };
}
