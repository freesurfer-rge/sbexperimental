#pragma once

#include <memory>
#include <string>
#include <vector>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xercesguard.hpp"
#include "configuration/xercesstringdeleter.hpp"
#include "controlleditemdata.hpp"

#include "signalheaddata.hpp"

namespace Signalbox {
  class ConfigReader : private XercesGuard {
  public:
    ConfigReader( const std::string& filename );

    void ReadControlledItems( std::vector< std::unique_ptr<ControlledItemData>>& items );
  private:
    std::unique_ptr<xercesc::XercesDOMParser> configFileParser;

    xercesc::DOMElement* GetSignalBoxElement();
    ControlledItemData* ReadSignalHead(xercesc::DOMElement* currentElement );
  };
}
