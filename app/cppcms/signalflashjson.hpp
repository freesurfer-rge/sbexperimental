#pragma once

#include <cppcms/json.h>

#include "signalflash.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::SignalFlash> {
      static Signalbox::SignalFlash get(value const& v);

      static void set(value& v, Signalbox::SignalFlash const& sf );
    };
  }
}
