#include <sstream>

#include "turnoutmotorjson.hpp"

namespace cppcms {
  namespace json {
    Signalbox::TurnoutMotor traits<Signalbox::TurnoutMotor>::get(value const& v ) {
      std::stringstream msg;
      msg << "Converting JSON value "
	  << v
	  << " to TurnoutMotor is not supported";
      throw std::runtime_error(msg.str());
    }

    void traits<Signalbox::TurnoutMotor>::set(value& v,
					      Signalbox::TurnoutMotor const& tm ) {
      v.set("id", tm.getId().ToString());
      v.set("state", Signalbox::ToString(tm.getState()));
    }
  }
}
