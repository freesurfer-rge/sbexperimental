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
    return &(this->trackCircuitMonitorFactory);
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

  size_t ControlledItemManager::ActivateItems() {
    size_t count = 0;
    for( auto it=this->items.begin(); it!=this->items.end(); ++it ) {
      it->second->Activate();
      count++;
    }

    return count;
  }

  ControlledItem* ControlledItemManager::GetById(const ItemId id) {
    if( this->items.count(id) == 0 ) {
      std::stringstream msg;
      msg << "Item not found: " << id;
      throw std::runtime_error(msg.str());
    }
    return this->items.at(id).get();
  }

  std::vector<ControlledItem*> ControlledItemManager::GetAllItems() {
    std::vector<ControlledItem*> result;

    for( auto it=this->items.begin(); it!=this->items.end(); ++it ) {
      result.push_back(it->second.get());
    }
    
    return result;
  }
}
