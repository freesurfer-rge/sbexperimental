#include "trackcircuitdata.hpp"

namespace Signalbox {
  std::vector<ControlledItemDataError> TrackCircuitData::GetErrors() const {
    throw std::runtime_error("TrackCircuitData::GetErrors not implemented");
  }

  ControlledItemFactory* TrackCircuitData::GetFactory(ControlledItemFactorySelector* factorySelector) const {
    throw std::runtime_error("TrackCircuitData::GetFactory not implemented");
  }
}
