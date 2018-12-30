#include "cppcmsdriver.hpp"
#include "cppcmsdriverselector.hpp"

namespace Signalbox {
  static CPPCMSDriverSelector cos;
  static CPPCMSDriver cppcmsDrv;

  ControlledItemDriver* CPPCMSDriverSelector::GetDriver() {
    return &cppcmsDrv;
  }
}
