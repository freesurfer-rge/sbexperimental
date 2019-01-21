#include "configuration/utils.hpp"

namespace Signalbox {
  namespace Configuration {
    std::unique_ptr<XMLCh,Configuration::xercesstringdeleter> GetTranscoded( const std::string& str ) {
      XMLCh* tc = xercesc::XMLString::transcode(str.c_str());
      return std::unique_ptr<XMLCh,Configuration::xercesstringdeleter>(tc,Configuration::xercesstringdeleter());
    }
  }
}
