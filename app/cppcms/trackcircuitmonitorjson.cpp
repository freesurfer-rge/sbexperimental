#include <sstream>

#include "trackcircuitmonitorjson.hpp"

namespace cppcms {
  namespace json {
    Signalbox::TrackCircuitMonitor traits<Signalbox::TrackCircuitMonitor>::get(value const& v ) {
      std::stringstream msg;
      msg << "Converting JSON value "
	  << v
	  << " to TrackCircuitMonitor is not supported";
      throw std::runtime_error(msg.str());
    }

    void traits<Signalbox::TrackCircuitMonitor>::set(value& v,
						     Signalbox::TrackCircuitMonitor const& tcm ) {
      v.set("id", tcm.getId().ToString());
      v.set("occupied", tcm.Get());
    }
  }
}
