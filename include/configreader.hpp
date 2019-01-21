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

    void ReadConfiguration( std::vector< std::unique_ptr<ControlledItemData> >& items );
  private:
    std::unique_ptr<xercesc::XercesDOMParser> configFileParser;

    std::unique_ptr<XMLCh,Configuration::xercesstringdeleter> ATTR_id;

    std::unique_ptr<XMLCh,Configuration::xercesstringdeleter> ATTR_aspectCount;
    
    std::unique_ptr<XMLCh,Configuration::xercesstringdeleter> TAG_OutputPin;
    std::unique_ptr<XMLCh,Configuration::xercesstringdeleter> ATTR_OutputPin_control;

    void ReadControlledItems(xercesc::DOMElement* elementSignalbox,
			     std::vector<std::unique_ptr<ControlledItemData>>& items );
    ControlledItemData* ReadSignalHead(xercesc::DOMElement* currentElement );
    void ReadSignalHeadOutputPin( xercesc::DOMElement* currentPin, SignalHeadData* signal );
  };
}
