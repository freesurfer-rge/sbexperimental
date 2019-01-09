#pragma once

#include "pinmanager.hpp"
#include "mappinmanager.hpp"

#include "consoledigitaloutputpin.hpp"
#include "consoledigitalinputpin.hpp"

namespace Signalbox {
  class ConsolePinManager : public MapPinManager<std::string,ConsoleDigitalInputPin,ConsoleDigitalOutputPin> {
  public:
    ConsolePinManager() :
      MapPinManager() {}
    
  protected:
    virtual std::string parsePinId( const std::string idString ) const override;

    virtual void setupInputPin( ConsoleDigitalInputPin* pin, const std::string pinId ) const override;

    virtual void setupOutputPin( ConsoleDigitalOutputPin* pin, const std::string pinId ) const override;
  };
}
