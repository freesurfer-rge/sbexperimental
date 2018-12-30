#include "itemidjson.hpp"

namespace cppcms {
  namespace json {
    Signalbox::ItemId traits<Signalbox::ItemId>::get(value const& v) {
      Signalbox::ItemId item;
      item.Parse(v.str());
      return item;;
    }

    void traits<Signalbox::ItemId>::set(value& v, Signalbox::ItemId const& id ) {
      v.str() = id.ToString();
    }
  }
}
