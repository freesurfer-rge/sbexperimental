#pragma once

#include <map>

#include "digitalinputpin.hpp"

namespace Signalbox {
  class MockPinManager;

  class MockDigitalInputPin : public DigitalInputPin {
  public:
    MockDigitalInputPin() :
      DigitalInputPin(),
      id(),
      createSettings(),
      state(false) {}
    
    virtual bool Get() const override;

    void Set(const bool level);

    std::string id;
    std::map<std::string,std::string> createSettings;
  private:
    friend class MockPinManager;

    bool state;
  };
}
