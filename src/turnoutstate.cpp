#include <boost/bimap.hpp>

#include "turnoutstate.hpp"

namespace Signalbox {
  static boost::bimap<TurnoutState,std::string> convertor;

  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(TurnoutState::Straight, "Straight") );
    convertor.insert( pos(TurnoutState::Curved, "Curved") );
  }
  
  std::ostream& operator<<( std::ostream& os, const TurnoutState s ) {
    os << ToString( s );
    
    return os;
  }
  
  std::string ToString( const TurnoutState s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    std::string res;
    try {
      res = convertor.left.at(s);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised TurnoutState: ";
      msg << static_cast<int>(s);
      throw std::runtime_error(msg.str());
    }
    
    return res;
  }
  
  void Parse( const std::string str, TurnoutState& s ) {
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
      msg << "' to TurnoutState";
      throw std::out_of_range(msg.str());
    }
  }
}
