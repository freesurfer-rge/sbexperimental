#pragma once

namespace Signalbox {
  class xercesstringdeleter {
  public:
    void operator()( char* str );
    
    void operator()( XMLCh* str );
  };
}
