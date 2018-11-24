#include <iostream>

#include "consoleloop.hpp"

namespace Signalbox {
  void consoleloop( std::map<ItemId,std::unique_ptr<SignalHead>>& sigs ) {
    bool done = false;

    while( !done ) {
      std::string inputLine;

      std::cin >> inputLine;

      if( inputLine == "q" ) {
	std::cout << "Received quit" << std::endl;
	done = true;
      }
    }
  }
}
