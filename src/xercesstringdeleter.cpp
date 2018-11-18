#include <xercesc/util/XMLString.hpp>

#include "xercesstringdeleter.hpp"

namespace Signalbox {
  void xercesstringdeleter::operator()( char* str ) {
    xercesc::XMLString::release( &str );
  }
  
  void xercesstringdeleter::operator()( XMLCh* str ) {
    xercesc::XMLString::release( &str );
  }
}
