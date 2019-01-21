#include "configuration/utils.hpp"

namespace Signalbox {
  namespace Configuration {
    std::unique_ptr<XMLCh,Configuration::xercesstringdeleter> GetTranscoded( const std::string& str ) {
      XMLCh* tc = xercesc::XMLString::transcode(str.c_str());
      return std::unique_ptr<XMLCh,Configuration::xercesstringdeleter>(tc,Configuration::xercesstringdeleter());
    }

    bool IsOutputPin( const xercesc::DOMElement* element ) {
      auto TAG_OutputPin = GetTranscoded("OutputPin");
      
      return xercesc::XMLString::equals(element->getTagName(), TAG_OutputPin.get());
    }
  }
}
