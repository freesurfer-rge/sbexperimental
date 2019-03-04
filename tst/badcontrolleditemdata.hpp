#pragma once

#include "controlleditemdata.hpp"

class BadControlledItemData : public Signalbox::ControlledItemData {
public:
  virtual std::vector<Signalbox::ControlledItemDataError> GetErrors() const override {
    return std::vector<Signalbox::ControlledItemDataError>();
  }
  
  virtual Signalbox::ControlledItemFactory* GetFactory(Signalbox::ControlledItemFactorySelector* factorySelector) const override {
    BOOST_WARN( factorySelector );
    throw std::runtime_error("BadControlledItemData::GetFactory Not Implemented!");
  }
};
