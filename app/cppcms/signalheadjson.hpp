#pragma once

#include <cppcms/json.h>

#include "signalhead.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::SignalHead> {
      static Signalbox::SignalHead get(value const& v) {
	throw std::runtime_error("get SignalHead from JSON not supported");
      }

      static void set(value& v, Signalbox::SignalHead const& sh ) {
	v.set("id", sh.getId().ToString());
	v.set("aspectCount", sh.getAspectCount());
	v.set("aspect", Signalbox::ToString(sh.getAspect()));
	v.set("flash", Signalbox::ToString(sh.getFlash()));
      }
    };
  }
}
