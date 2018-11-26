#pragma once

#include <memory>
#include <string>
#include <vector>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xercesguard.hpp"
#include "xercesstringdeleter.hpp"
#include "controlleditem.hpp"

#include "signalheaddata.hpp"

namespace Signalbox {
  class ConfigReader : private XercesGuard {
  public:
    ConfigReader( const std::string& filename );

    void ReadConfiguration( std::vector< std::unique_ptr<ControlledItem> >& items );
  private:
    std::unique_ptr<xercesc::XercesDOMParser> configFileParser;

    std::unique_ptr<XMLCh,xercesstringdeleter> ATTR_id;

    std::unique_ptr<XMLCh,xercesstringdeleter> ATTR_aspectCount;
    
    std::unique_ptr<XMLCh,xercesstringdeleter> TAG_OutputPin;
    std::unique_ptr<XMLCh,xercesstringdeleter> ATTR_OutputPin_control;

    void ReadControlledItems(xercesc::DOMElement* elementSignalbox,
			     std::vector<std::unique_ptr<ControlledItem>>& items );
    ControlledItem* ReadSignalHead(xercesc::DOMElement* currentElement );
    void ReadSignalHeadOutputPin( xercesc::DOMElement* currentPin, SignalHeadData* signal );
  };
}
