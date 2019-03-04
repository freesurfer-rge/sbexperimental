#pragma once

#include <map>
#include <memory>
#include <sstream>

#include <boost/predef.h>

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

    virtual DigitalInputPin* CreateDigitalInputPin(const DigitalInputPinData& data) override {
      const PinIdType parsedId = this->parsePinId(data.id);
      this->throwIfPinExists(parsedId);

      auto nxt = std::unique_ptr<DigitalInputPinType>(new DigitalInputPinType());
      this->setupInputPin(nxt.get(), data);

      this->inputPins[parsedId] = std::move(nxt);

      return this->inputPins[parsedId].get();
    }

    virtual DigitalOutputPin* CreateDigitalOutputPin(const std::string pinId) override {
      const PinIdType parsedId = this->parsePinId(pinId);
      this->throwIfPinExists(parsedId);

      auto nxt = std::unique_ptr<DigitalOutputPinType>(new DigitalOutputPinType());
      this->setupOutputPin(nxt.get(), parsedId);

      this->outputPins[parsedId] = std::move(nxt);

      return this->outputPins[parsedId].get();
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

#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
    virtual void setupInputPin( DigitalInputPinType* pin, const DigitalInputPinData& data ) const {}

    virtual void setupOutputPin( DigitalOutputPinType* pin, const PinIdType pinId ) const {}
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clange diagnostic pop
#endif
    
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
