#pragma once

#include <string>
#include "itemid.hpp"

namespace Signalbox {
  struct ItemInfo {
    ItemInfo() : id(), type() {}
    
    ItemId id;
    std::string type;
  };
}
