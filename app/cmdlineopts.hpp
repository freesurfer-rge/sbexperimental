#pragma once

#include <string>

namespace Signalbox {
  class CmdLineOpts {
  public:
    CmdLineOpts() : helpMessagePrinted(false),
		    configFilePath() {}
    
    bool helpMessagePrinted;
    std::string configFilePath;

    void Populate( int argc, char* argv[] );
  };
}
