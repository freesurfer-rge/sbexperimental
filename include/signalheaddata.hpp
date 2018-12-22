#pragma once

#include <map>
#include <string>

#include "controlleditemdata.hpp"

#include "signalheadpins.hpp"

namespace Signalbox {
  class SignalHeadData : public ControlledItemData {
  public:
    SignalHeadData() : ControlledItemData(),
		       aspectCount(0),
		       pinData() {}
    
    char aspectCount;
    std::map<SignalHeadPins,std::string> pinData;

    virtual std::vector<ControlledItemDataError> GetErrors() const override;

    virtual ControlledItemFactory* GetFactory(ControlledItemFactorySelector* factorySelector) const override;
  private:
    std::vector<ControlledItemDataError> GetAspectErrors() const;

    std::vector<ControlledItemDataError> GetPinErrors() const;
  };
}
