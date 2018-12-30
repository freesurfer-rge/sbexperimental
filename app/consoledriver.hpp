#pragma once

#include <string>
#include <vector>

#include "controlleditemdriver.hpp"

namespace Signalbox {
  class ConsoleDriver : public ControlledItemDriver {
  public:
    virtual void Run(ControlledItemFetcher* f) override;

  private:
    void stringtotokens( const std::string s,
			 std::vector<std::string>& tokens ) const;
  };
}
