#pragma once

#include "pinmanager.hpp"

#include "controlleditemfactory.hpp"

namespace Signalbox {
  class SignalHeadFactory : public ControlledItemFactory {
  public:
    SignalHeadFactory(PinManager* pm) :
      pinManager(pm) {}
    
    virtual std::unique_ptr<ControlledItem> Manufacture(const ControlledItemData* cid) override;

  private:
    PinManager* pinManager;
  };
}
