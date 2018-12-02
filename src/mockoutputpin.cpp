#include "mockoutputpin.hpp"

namespace Signalbox {
  std::map<std::string,MockOutputPin*> MockOutputPin::allPins;
  
  void MockOutputPin::TurnOn() {
    this->isOn.store(true, std::memory_order_seq_cst);
  }

  void MockOutputPin::TurnOff() {
    this->isOn.store(false, std::memory_order_seq_cst);
  }

  std::unique_ptr<OutputPin> MockOutputPin::manufacture(const std::string pinId) {
    auto res = std::unique_ptr<MockOutputPin>(new MockOutputPin());
    res->pin = pinId;

    MockOutputPin::allPins[pinId] = res.get();
    
    return std::unique_ptr<OutputPin>(res.release());
  }
}
