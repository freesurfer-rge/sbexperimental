#pragma once

#include <map>
#include <string>

#include "controlleditem.hpp"

#include "signalheadpins.hpp"

namespace Signalbox {
  class SignalHeadData : public ControlledItem {
  public:
    SignalHeadData() : ControlledItem(),
		       aspectCount(0),
		       pinData() {}
    
    char aspectCount;
    std::map<SignalHeadPins,std::string> pinData;

    virtual std::vector<ControlledItemError> GetErrors() const override;

  private:
    std::vector<ControlledItemError> GetAspectErrors() const;

    std::vector<ControlledItemError> GetPinErrors() const;
  };
}
