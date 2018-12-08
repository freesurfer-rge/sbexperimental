#include <stdexcept>
#include <sstream>

#include "controlleditemmanager.hpp"

namespace Signalbox {
  ControlledItemFactory* ControlledItemManager::GetSignalHeadFactory() {
    return &(this->signalHeadFactory);
  }

  ControlledItemFactory* ControlledItemManager::GetTurnoutMotorFactory() {
    std::stringstream msg;
    msg << __PRETTY_FUNCTION__
	<< ": Not implemented";
    throw std::runtime_error(msg.str());
  }

  ControlledItemFactory* ControlledItemManager::GetTrackCircuitMonitorFactory() {
    std::stringstream msg;
    msg << __PRETTY_FUNCTION__
	<< ": Not implemented";
    throw std::runtime_error(msg.str());
  }
}