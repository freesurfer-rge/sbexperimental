#include <iostream>

#include "xercesc/util/PlatformUtils.hpp"

#include "xercesguard.hpp"

namespace Signalbox {
  XercesGuard::XercesGuard() {
    xercesc::XMLPlatformUtils::Initialize();
  }

  XercesGuard::~XercesGuard() {
    xercesc::XMLPlatformUtils::Terminate();
  }
}
