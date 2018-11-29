
#pragma once

#include <string>

namespace Signalbox {
  class CmdLineOpts {
  public:
    CmdLineOpts() : helpMessagePrinted(false),
		    configFilePath(),
		    outputDestination() {}
    
    bool helpMessagePrinted;
    std::string configFilePath;
    std::string outputDestination;

    void Populate( int argc, char* argv[] );
  };
}
