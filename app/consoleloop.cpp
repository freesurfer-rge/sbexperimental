#include <iostream>
#include <sstream>
#include <locale>

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

  
  void consoleloop( std::map<ItemId,std::unique_ptr<SignalHead>>& sigs ) {
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
	}
	catch( std::exception& e ) {
	  std::cerr << e.what() << std::endl;
	  continue;
	}

	if( sigs.count(target) != 0 ) {
	  sigs[target]->SetState(aspect,flash);
	} else {
	  std::cerr << "Unrecognised Id: " << target << std::endl;
	}
      }
    }
  }
}
