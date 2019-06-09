#pragma once
#include <cppcms/json.h>

#include "turnoutmotor.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::TurnoutMotor> {
      static Signalbox::TurnoutMotor get(value const& v);

      static void set(value&v, Signalbox::TurnoutMotor const& tm);
    };
  }
}
