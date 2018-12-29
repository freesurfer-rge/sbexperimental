#pragma once

#include <cppcms/json.h>

#include "itemid.hpp"

namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::ItemId> {
      static Signalbox::ItemId get(value const& v);
	  
      static void set(value& v, Signalbox::ItemId const& id );
    };
  }
}
