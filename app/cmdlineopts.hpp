#pragma once

#include <string>

namespace Signalbox {
  class CmdLineOpts {
  public:
    CmdLineOpts() : helpMessagePrinted(false),
		    configFilePath() {}
    
    bool helpMessagePrinted;
    std::string configFilePath;
    std::string outputDestination;

    void Populate( int argc, char* argv[] );
  };
}
