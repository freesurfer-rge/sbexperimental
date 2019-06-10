#pragma once
#include <cppcms/json.h>

#include "turnoutmotor.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::TurnoutMotor> {
      // Note: return a reference since TurnoutMotor is abstract
      static Signalbox::TurnoutMotor& get(value const& v);

      static void set(value&v, Signalbox::TurnoutMotor const& tm);
    };
  }
}
