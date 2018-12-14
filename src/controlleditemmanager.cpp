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

  std::unique_ptr<ControlledItem> ControlledItemManager::CreateItem(const ControlledItemData* data) {
    auto itemFactory = data->GetFactory(this);

    return itemFactory->Manufacture(data);
  }

  size_t ControlledItemManager::PopulateItems(const std::vector<std::unique_ptr<ControlledItemData>>& items) {
    this->items.empty();

    for( auto it=items.begin(); it!=items.end(); ++it ) {
      if( this->items.count((*it)->id) ) {
	std::stringstream msg;
	msg << "Detected duplicate id: " << (*it)->id;
	throw std::runtime_error(msg.str());
      }
      this->items[(*it)->id] = this->CreateItem(it->get());
    }

    return this->items.size();
  }
}
