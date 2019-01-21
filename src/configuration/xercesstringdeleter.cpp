#include "configuration/xercesstringdeleter.hpp"

namespace Signalbox {
  namespace Configuration {
    void xercesstringdeleter::operator()( char* str ) {
      xercesc::XMLString::release( &str );
    }
  
    void xercesstringdeleter::operator()( XMLCh* str ) {
      xercesc::XMLString::release( &str );
    }
  }
}
