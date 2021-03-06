#pragma once

#include <memory>
#include <string>
#include <vector>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "configuration/xercesguard.hpp"
#include "configuration/xercesstringdeleter.hpp"

#include "controlleditemdata.hpp"
#include "railtrafficcontroldata.hpp"
#include "i2cbusdata.hpp"

namespace Signalbox {
  namespace Configuration {
    class ConfigReader : private XercesGuard {
    public:
      ConfigReader( const std::string& filename );
      
      void ReadRailTrafficControl( RailTrafficControlData& rtcData );

      void ReadI2CData( I2CBusData& i2cData );
      
      void ReadControlledItems( std::vector< std::unique_ptr<ControlledItemData>>& items );
    private:
      std::unique_ptr<xercesc::XercesDOMParser> configFileParser;
      
      xercesc::DOMElement* GetSignalBoxElement();
      ControlledItemData* ReadSignalHead(xercesc::DOMElement* currentElement );
      ControlledItemData* ReadTrackCircuitMonitor( xercesc::DOMElement* currentElement );
      ControlledItemData* ReadServoTurnoutMotor( xercesc::DOMElement* currentElement );
    };
  }
}
