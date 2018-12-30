#pragma once

#include <string>
#include "itemid.hpp"

namespace Signalbox {
  struct ItemInfo {
    ItemId id;
    std::string type;
  };
}
