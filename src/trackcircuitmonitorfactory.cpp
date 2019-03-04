#include <sstream>
#include <stdexcept>

#include "trackcircuitmonitordata.hpp"
#include "trackcircuitmonitor.hpp"

#include "trackcircuitmonitorfactory.hpp"

namespace Signalbox {
  std::unique_ptr<ControlledItem> TrackCircuitMonitorFactory::Manufacture(const ControlledItemData* cid) {
    auto tcmd = dynamic_cast<const TrackCircuitMonitorData*>(cid);
    if( tcmd == NULL ) {
      std::stringstream msg;
      msg << "Failed to cast ControlledItemData to TrackCircuitMonitorData";
      throw std::runtime_error(msg.str());
    }

    std::unique_ptr<TrackCircuitMonitor> res;
    res.reset( new TrackCircuitMonitor(tcmd->id) );

    res->pin = this->pinManager->CreateDigitalInputPin(tcmd->inputPin);
    res->rtc = this->rtcClient;
    
    return std::unique_ptr<ControlledItem>(res.release());
  }
}
