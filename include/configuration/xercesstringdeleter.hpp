#pragma once

#include <xercesc/util/XMLString.hpp>

namespace Signalbox {
  namespace Configuration {
    class xercesstringdeleter {
    public:
      void operator()( char* str );
      
      void operator()( XMLCh* str );
    };
  }
}
