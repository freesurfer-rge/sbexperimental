#include "trackcircuitmonitordata.hpp"

namespace Signalbox {
  std::vector<ControlledItemDataError> TrackCircuitMonitorData::GetErrors() const {
    throw std::runtime_error("TrackCircuitData::GetErrors not implemented");
  }

  ControlledItemFactory* TrackCircuitMonitorData::GetFactory(ControlledItemFactorySelector* factorySelector) const {
    throw std::runtime_error("TrackCircuitMonitorData::GetFactory not implemented");
  }
}
