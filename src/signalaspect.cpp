#include <boost/bimap.hpp>

#include "signalaspect.hpp"

namespace Signalbox {
  static boost::bimap<SignalAspect,std::string> convertor;

  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(SignalAspect::Inactive, "Inactive") );
    convertor.insert( pos(SignalAspect::Done, "Done") );
    convertor.insert( pos(SignalAspect::Red, "Red") );
    convertor.insert( pos(SignalAspect::Yellow, "Yellow") );
    convertor.insert( pos(SignalAspect::DoubleYellow, "DoubleYellow") );
    convertor.insert( pos(SignalAspect::Green, "Green") );
  }
  
  std::ostream& operator<<( std::ostream& os, const SignalAspect s ) {
    os << ToString( s );
    
    return os;
  }

  std::string ToString( const SignalAspect s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    std::string res;
    try {
      res = convertor.left.at(s);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised SignalAspect: ";
      msg << static_cast<int>(s);
      throw std::runtime_error(msg.str());
    }
    
    return res;
  }

  void Parse( const std::string str, SignalAspect& s ) {
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
      msg << "' to SignalAspect";
      throw std::out_of_range(msg.str());
    }
  }
}
