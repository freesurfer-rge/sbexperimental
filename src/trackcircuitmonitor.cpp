#include "trackcircuitmonitor.hpp"

namespace Signalbox {
  void TrackCircuitMonitor::Activate() {
    this->done = false;
    this->t = std::thread(&TrackCircuitMonitor::Run, this);
  }

  void TrackCircuitMonitor::Deactivate() {
    this->done = true;
  }

  void TrackCircuitMonitor::Run() {
    bool lastState = this->Get();
    this->rtc->SendTrackCircuitNotification( this->getId(), lastState );

    while( !(this->done) ) {
      const bool nxtState = this->pin->WaitFor(this->pollInterval);
      if( nxtState != lastState ) {
	lastState = nxtState;
	this->rtc->SendTrackCircuitNotification( this->getId(), nxtState );
      }
    }
  }
  
  bool TrackCircuitMonitor::Get() const {
    return this->pin->Get();
  }
}
