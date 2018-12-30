#include "signalflashjson.hpp"

namespace cppcms {
  namespace json {
    Signalbox::SignalFlash traits<Signalbox::SignalFlash>::get(value const& v) {
      Signalbox::SignalFlash res;
      Signalbox::Parse( v.str(), res );
      return res;
    }
    
    void traits<Signalbox::SignalFlash>::set(value& v,
					     Signalbox::SignalFlash const& sf ) {
      v.str() = Signalbox::ToString( sf );
    }
  }
}
