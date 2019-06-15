#pragma once
#include <map>
#include <memory>

#include <pigpiod_if2.h>

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

    virtual void Initialise(const std::vector<I2CDeviceData>& i2cDevices) {
      throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    
    virtual PWMChannel* CreatePWMChannel(const DeviceRequestData& data) override;
    
    // Remove copy constructor and operator=
    PiGPIOdPinManager(PiGPIOdPinManager&) = delete;
    PiGPIOdPinManager& operator=(PiGPIOdPinManager&) = delete;
  protected:
    virtual int parsePinId( const std::string idString ) const override;

    virtual void setupInputPin( PiGPIOdDigitalInputPin* pin, const DigitalInputPinData& data ) const override;

    virtual void setupOutputPin( PiGPIOdDigitalOutputPin* pin, const int pinId ) const override;
    
  private:
    static PiGPIOdPinManager* singleton;

    static void callBackDispatch(int pi, unsigned int user_gpio, unsigned int level, uint32_t tick);
    
    int piId;
  };
}
