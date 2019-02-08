#pragma once

#include "rtcselector.hpp"

#include "consolertcclientfactory.hpp"

namespace Signalbox {
  class ConsoleRTCSelector : public RTCSelector {
  public:
    ConsoleRTCSelector() :
      RTCSelector(),
      crtcclientf() {
      this->AddSelector( std::string("console"), this );
    }

    virtual RailTrafficControlClientFactory* GetRailTrafficControlClientFactory() override;

  private:
    ConsoleRTCClientFactory crtcclientf;
  };
}
