#include <iostream>

#include "xercesc/util/PlatformUtils.hpp"

#include "configuration/xercesguard.hpp"

namespace Signalbox {
  namespace Configuration {
    XercesGuard::XercesGuard() {
      xercesc::XMLPlatformUtils::Initialize();
    }

    XercesGuard::~XercesGuard() {
      xercesc::XMLPlatformUtils::Terminate();
    }
  }
}
