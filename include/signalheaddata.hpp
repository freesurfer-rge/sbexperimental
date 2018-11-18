#pragma once

#include <map>

#include "controlleditem.hpp"

#include "signalheadpins.hpp"

namespace Signalbox {
  class SignalHeadData : public ControlledItem {
  public:
    char aspectCount;
    std::map<SignalHeadPins,char> pinData;

    virtual std::vector<ControlledItemError> GetErrors() const override;

  private:
    std::vector<ControlledItemError> GetAspectErrors() const;

    std::vector<ControlledItemError> GetPinErrors() const;
  };
}
