#include <iostream>
#include <sstream>
#include <locale>

#include "signalhead.hpp"

#include "consoleloop.hpp"

namespace Signalbox {
  void stringtotokens( const std::string s, std::vector<std::string>& tokens ) {
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

  
  void consoleloop( ControlledItemManager* cim ) {
    bool done = false;

    while( !done ) {
      std::string inputLine;

      std::getline( std::cin, inputLine );

      if( inputLine == "q" ) {
	std::cout << "Received quit" << std::endl;
	done = true;
      } else {
	std::vector<std::string> tokens;
	stringtotokens(inputLine, tokens);

	if( tokens.size() != 3 ) {
	  std::cerr << "Did not find three tokens" << std::endl;
	  continue;
	}

	ItemId target;
	SignalAspect aspect;
	SignalFlash flash;

	try {
	  target.Parse(tokens.at(0));
	  Parse(tokens.at(1), aspect);
	  Parse(tokens.at(2), flash);

	  auto ci = cim->GetById(target);

	  auto sig = dynamic_cast<SignalHead*>(ci);

	  if( sig != NULL ) {
	    sig->SetState(aspect,flash);
	  } else {
	    std::cerr << "Could not cast to SignalHead" << std::endl;
	  }
	}
	catch( std::exception& e ) {
	  std::cerr << e.what() << std::endl;
	  continue;
	}
      }
    }
  }
}
