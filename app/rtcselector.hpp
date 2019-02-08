#pragma once

#include <map>
#include <string>
#include <memory>

#include "railtrafficcontrolclientfactory.hpp"

namespace Signalbox {
  class RTCSelector {
  public:
    static std::string ListRTCSelectors();

    static RTCSelector* GetSelector( std::string name );

    virtual ~RTCSelector() {}

    virtual RailTrafficControlClientFactory* GetRailTrafficControlClientFactory() = 0;

  protected:
    void AddSelector(std::string name, RTCSelector* s) {
      RTCSelector::selectors[name] = s;
    }

  private:
    static std::map<std::string,RTCSelector*> selectors;
  };
}
