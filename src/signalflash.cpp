#include <boost/bimap.hpp>

#include "signalflash.hpp"

namespace Signalbox {
  static boost::bimap<SignalFlash,std::string> convertor;

  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(SignalFlash::Steady, "Steady") );
    convertor.insert( pos(SignalFlash::Flashing, "Flashing") );
  }
  
  std::ostream& operator<<( std::ostream& os, const SignalFlash s ) {
    os << ToString( s );
    
    return os;
  }

  std::string ToString( const SignalFlash s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    std::string res;
    try {
      res = convertor.left.at(s);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised SignalFlash: ";
      msg << static_cast<int>(s);
      throw std::runtime_error(msg.str());
    }
    
    return res;
  }

  void Parse( const std::string str, SignalFlash& s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    try {
      s = convertor.right.at(str);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Could not parse '";
      msg << str;
      msg << "' to SignalFlash";
      throw std::out_of_range(msg.str());
    }
  }
}
