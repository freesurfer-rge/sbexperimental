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

    void handlesignalhead( ControlledItem* target, std::vector<std::string>& tokens );

    void handleturnoutmotor( ControlledItem* target, std::vector<std::string>& tokens );
  };
}
