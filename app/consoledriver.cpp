#include <iostream>
#include <sstream>
#include <locale>

#include "signalhead.hpp"
#include "turnoutmotor.hpp"

#include "consoledriver.hpp"

namespace Signalbox {
  void ConsoleDriver::Run(ControlledItemFetcher* f) {
    bool done = false;

    while( !done ) {
      std::string inputLine;
      
      std::getline( std::cin, inputLine );
      
      if( inputLine == "q" ) {
	std::cout << "Received quit" << std::endl;
	done = true;
      } else {
	std::vector<std::string> tokens;
	this->stringtotokens(inputLine, tokens);
	
	ItemId target;
	
	try {
	  target.Parse(tokens.at(0));
	  
	  auto ci = f->GetById(target);

	  if( ci->getTypeString() == "signalhead" ) {
	    this->handlesignalhead( ci, tokens );
	  } else if( ci->getTypeString() == "turnoutmotor" ) {
	    this->handleturnoutmotor( ci, tokens );
	  } else {
	    std::cerr << "ControlledItem type '"
		      << ci->getTypeString()
		      << "' is not supported here"
		      << std::endl;
	  }
	}
	catch( std::exception& e ) {
	  std::cerr << e.what() << std::endl;
	  continue;
	}
      }
    }
  }

  void ConsoleDriver::handlesignalhead( ControlledItem* target, std::vector<std::string>& tokens ) {
    auto sig = dynamic_cast<SignalHead*>(target);
    
    if( tokens.size() != 3 ) {
      std::cerr << "Did not find three tokens for SignalHead" << std::endl;
      return;
    }
    
    SignalAspect aspect;
    SignalFlash flash;

    Parse(tokens.at(1), aspect);
    Parse(tokens.at(2), flash);

    if( sig != NULL ) {
      sig->SetState(aspect,flash);
    } else {
      std::cerr << "Could not cast to SignalHead" << std::endl;
    }
  }

   void ConsoleDriver::handleturnoutmotor( ControlledItem* target, std::vector<std::string>& tokens ) {
    auto tm = dynamic_cast<TurnoutMotor*>(target);
    
    if( tokens.size() != 2 ) {
      std::cerr << "Did not find three tokens for TurnoutMotor" << std::endl;
      return;
    }
    
    TurnoutState tms;

    Parse(tokens.at(1), tms);

    if( tm != NULL ) {
      tm->SetState(tms);
    } else {
      std::cerr << "Could not cast to TurnoutMotor" << std::endl;
    }
  }
  
  void ConsoleDriver::stringtotokens( const std::string s,
				      std::vector<std::string>& tokens ) const {
    tokens.clear();
    
    std::stringstream nxt;
    for( auto c=s.begin(); c!=s.end(); ++c ) {
      if( std::isspace(*c) ) {
	if( nxt.tellp() != 0 ) {
	  // Just completed a token
	  tokens.push_back(nxt.str());
	  nxt.str(std::string());
	}
      } else {
	nxt << (*c);
      }
    }
    // Need to catch case where token ends line
    if( nxt.tellp() != 0 ) {
      // Just completed a token
      tokens.push_back(nxt.str());
    }
  }
}
