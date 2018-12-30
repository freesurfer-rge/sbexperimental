#pragma once
#include <cppcms/json.h>

#include "signalhead.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::SignalHead> {
      static Signalbox::SignalHead get(value const& v);

      static void set(value& v, Signalbox::SignalHead const& sh );
    };
  }
}
