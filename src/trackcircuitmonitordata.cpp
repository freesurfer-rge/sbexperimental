#include "trackcircuitmonitordata.hpp"

namespace Signalbox {
  std::vector<ControlledItemDataError> TrackCircuitMonitorData::GetErrors() const {
    std::vector<ControlledItemDataError> result;

    if( this->id == ItemId(0) ) {
      ControlledItemDataError e;
      e.message = "Invalid id";
      result.push_back(e);
    }

    return result;
  }

  ControlledItemFactory* TrackCircuitMonitorData::GetFactory(ControlledItemFactorySelector* factorySelector) const {
    return factorySelector->GetTrackCircuitMonitorFactory();
  }
}
