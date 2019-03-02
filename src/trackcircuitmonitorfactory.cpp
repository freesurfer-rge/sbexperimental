#include <sstream>
#include <stdexcept>

#include "trackcircuitmonitordata.hpp"
#include "trackcircuitmonitor.hpp"

#include "trackcircuitmonitorfactory.hpp"

namespace Signalbox {
  std::unique_ptr<ControlledItem> TrackCircuitMonitorFactory::Manufacture(const ControlledItemData* cid) {
    throw std::runtime_error("TCMFactory not implemented");
  }
}
