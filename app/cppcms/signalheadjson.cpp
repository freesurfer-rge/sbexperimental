#include <sstream>

#include "signalheadjson.hpp"

namespace cppcms {
  namespace json {
    Signalbox::SignalHead traits<Signalbox::SignalHead>::get(value const& v) {
      std::stringstream msg;
      msg << "Converting JSON value "
	  << v
	  << " to SignalHead is not supported";
      throw std::runtime_error(msg.str());
    }
    
    void traits<Signalbox::SignalHead>::set(value& v,
					    Signalbox::SignalHead const& sh ) {
      v.set("id", sh.getId().ToString());
      v.set("aspectCount", sh.getAspectCount());
      v.set("aspect", Signalbox::ToString(sh.getAspect()));
      v.set("flash", Signalbox::ToString(sh.getFlash()));
    }
  }
}
