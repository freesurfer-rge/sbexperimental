#pragma once
#include <cppcms/json.h>

#include "trackcircuitmonitor.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::TrackCircuitMonitor> {
      static Signalbox::TrackCircuitMonitor get(value const& v);

      static void set(value&v, Signalbox::TrackCircuitMonitor const& tcm);
    };
  }
}
