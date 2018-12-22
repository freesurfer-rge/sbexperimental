#pragma once

#include "pinmanager.hpp"

#include "controlleditemfactory.hpp"

namespace Signalbox {
  class SignalHeadFactory : public ControlledItemFactory {
  public:
    SignalHeadFactory(PinManager* pm) :
      pinManager(pm) {}
    
    virtual std::unique_ptr<ControlledItem> Manufacture(const ControlledItemData* cid) override;

    // Remove copy constructor and operator=
    SignalHeadFactory(SignalHeadFactory&) = delete;
    SignalHeadFactory& operator=(SignalHeadFactory&) = delete;
  private:
    PinManager* pinManager;
  };
}
