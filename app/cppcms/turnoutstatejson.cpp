#include "turnoutstatejson.hpp"

namespace cppcms {
  namespace json {
    Signalbox::TurnoutState traits<Signalbox::TurnoutState>::get(value const& v) {
      Signalbox::TurnoutState res;
      Signalbox::Parse( v.str(), res );
      return res;
    }
    
    void traits<Signalbox::TurnoutState>::set(value& v,
					      Signalbox::TurnoutState const& ts ) {
      v.str() = Signalbox::ToString( ts );
    }
  }
}
