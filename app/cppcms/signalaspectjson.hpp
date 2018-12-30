#pragma once

#include <cppcms/json.h>

#include "signalaspect.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::SignalAspect> {
      static Signalbox::SignalAspect get(value const& v);

      static void set(value& v, Signalbox::SignalAspect const& sa );
    };
  }
}
