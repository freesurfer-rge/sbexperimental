#pragma once
#include <map>

#include "signalhead.hpp"

namespace Signalbox {
  void consoleloop( std::map<ItemId,std::unique_ptr<SignalHead>>& sigs );
}
