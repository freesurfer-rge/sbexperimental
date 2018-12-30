#pragma once
#include <cppcms/json.h>

#include "iteminfo.hpp"


namespace cppcms {
  namespace json {
    template<>
    struct traits<Signalbox::ItemInfo> {
      static Signalbox::ItemInfo get(value const& v);

      static void set(value& v, Signalbox::ItemInfo const& sh );
    };
  }
}
