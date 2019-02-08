
#pragma once

#include <string>

namespace Signalbox {
  class CmdLineOpts {
  public:
    CmdLineOpts() : helpMessagePrinted(false),
		    configFilePath(),
		    outputDestination(),
		    driver() {}
    
    bool helpMessagePrinted;
    std::string configFilePath;
    std::string outputDestination;
    std::string driver;
    std::string rtcClient;

    void Populate( int argc, char* argv[] );
  };
}
