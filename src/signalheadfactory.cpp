#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "signalheadfactory.hpp"

namespace Signalbox {
  std::unique_ptr<ControlledItem> SignalHeadFactory::Manufacture(const ControlledItemData* cid) {
    throw std::runtime_error("Not yet implemented");
  }
}
