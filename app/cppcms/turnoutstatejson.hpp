#pragma once

#include <cppcms/json.h>

#include "turnoutstate.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::TurnoutState> {
      static Signalbox::TurnoutState get(value const& v);

      static void set(value& v, Signalbox::TurnoutState const& ts );
    };
  }
}
