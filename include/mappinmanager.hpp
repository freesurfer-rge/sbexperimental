#pragma once

#include <map>
#include <memory>

#include "pinmanager.hpp"

namespace Signalbox {
  template<typename PinIdType,
	   typename DigitalInputPinType,
	   typename DigitalOutputPinType>
  class MapPinManager : public PinManager {
  public:
    MapPinManager() :
      PinManager(),
      outputPins(),
      inputPins() {}

    DigitalInputPin* CreateDigitalInputPin(const std::string pinId) {
      const PinIdType parsedId = this->parsePinId(pinId);
      this->throwIfPinExists(parsedId);

      auto nxt = std::unique_ptr<DigitalInputPinType>(new DigitalInputPinType());
      this->setupInputPin(nxt.get(), parsedId);

      this->inputPins[pinId] = std::move(nxt);

      return this->inputPins[pinId].get();
    }

    DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) {
      const PinIdType parsedId = this->parsePinId(pinId);
      this->throwIfPinExists(parsedId);

      auto nxt = std::unique_ptr<DigitalOutputPinType>(new DigitalOutputPinType());
      this->setupOutputPin(nxt.get(), parsedId);

      this->outputPins[pinId] = std::move(nxt);

      return this->outputPins[pinId].get();
    }
    
  protected:
    void clearAllPins() {
      this->outputPins.clear();
      this->inputPins.clear();
    }

    size_t getOutputPinCount() const {
      return this->outputPins.size();
    }

    size_t getInputPinCount() const {
      return this->inputPins.size();
    }
    
    DigitalOutputPinType* getOutputPin(const PinIdType id) const {
      return this->outputPins.at(id).get();
    }

    DigitalInputPinType* getInputPin(const PinIdType id) const {
      return this->inputPins.at(id).get();
    }

    virtual PinIdType parsePinId( const std::string idString ) const = 0;

    virtual void setupInputPin( DigitalInputPinType* pin, const PinIdType pinId ) const = 0;

    virtual void setupOutputPin( DigitalOutputPinType* pin, const PinIdType pinId ) const = 0;
    
  private:
    std::map<PinIdType,std::unique_ptr<DigitalOutputPinType>> outputPins;
    std::map<PinIdType,std::unique_ptr<DigitalInputPinType>> inputPins;
    
    void throwIfPinExists( const PinIdType pinId ) const {
      if( this->outputPins.count(pinId) != 0 ) {
	std::stringstream msg;
	msg << "Pin '" << pinId << "' already exists as OutputPin";
	throw std::runtime_error(msg.str());
      }
      if( this->inputPins.count(pinId) != 0 ) {
	std::stringstream msg;
	msg << "Pin '" << pinId << "' already exists as InputPin";
	throw std::runtime_error(msg.str());
      }
    }
  };
}
