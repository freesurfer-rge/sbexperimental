#pragma once

namespace Signalbox {
  namespace Configuration {
    class xercesstringdeleter {
    public:
      void operator()( char* str );
      
      void operator()( XMLCh* str );
    };
  }
}
