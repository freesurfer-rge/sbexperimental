#include "signalaspectjson.hpp"

namespace cppcms {
  namespace json {
    Signalbox::SignalAspect traits<Signalbox::SignalAspect>::get(value const& v) {
      Signalbox::SignalAspect res;
      Signalbox::Parse( v.str(), res );
      return res;
    }
    
    void traits<Signalbox::SignalAspect>::set(value& v,
					      Signalbox::SignalAspect const& sa ) {
      v.str() = Signalbox::ToString( sa );
    }
  }
}
