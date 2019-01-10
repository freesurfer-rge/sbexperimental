#pragma once
#include <map>
#include <memory>


#include "pinmanager.hpp"
#include "mappinmanager.hpp"

#include "pigpioddigitaloutputpin.hpp"
#include "pigpioddigitalinputpin.hpp"

namespace Signalbox {
  class PiGPIOdPinManager : public MapPinManager<int,PiGPIOdDigitalInputPin,PiGPIOdDigitalOutputPin> {
  public:
    PiGPIOdPinManager();

    ~PiGPIOdPinManager();
    
    int ParseId(const std::string pinId) const {
      return this->parsePinId(pinId);
    }

    int GetPiId() const {
      return this->piId;
    }

    // Remove copy constructor and operator=
    PiGPIOdPinManager(PiGPIOdPinManager&) = delete;
    PiGPIOdPinManager& operator=(PiGPIOdPinManager&) = delete;
  protected:
    virtual int parsePinId( const std::string idString ) const override;

    virtual void setupInputPin( PiGPIOdDigitalInputPin* pin, const int pinId ) const override;

    virtual void setupOutputPin( PiGPIOdDigitalOutputPin* pin, const int pinId ) const override;
    
  private:
    static bool exists;
    
    int piId;
  };
}
