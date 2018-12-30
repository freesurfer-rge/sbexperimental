#include <sstream>

#include "itemidjson.hpp"

#include "iteminfojson.hpp"


namespace cppcms {
  namespace json {
    Signalbox::ItemInfo traits<Signalbox::ItemInfo>::get(value const& v) {
      std::stringstream msg;
      msg << "Converting JSON value "
	  << v
	  << " to ItemInfo is not supported";
      throw std::runtime_error(msg.str());
    }
    
    void traits<Signalbox::ItemInfo>::set(value& v,
					  Signalbox::ItemInfo const& info ) {
      v.set("id", info.id.ToString());
      v.set("type", info.type);
    }
  }
}
