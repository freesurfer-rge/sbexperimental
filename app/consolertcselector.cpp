#include "consolertcselector.hpp"

namespace Signalbox {
  static ConsoleRTCSelector crtcs;

  RailTrafficControlClientFactory* ConsoleRTCSelector::GetRailTrafficControlClientFactory() {
    return &(this->crtcclientf);
  }
}
