#include "digitalinputpin.hpp"

namespace Signalbox {
  bool DigitalInputPin::Wait() {
    std::unique_lock<std::mutex> lck(this->mtx);
    this->last = this->Get();
    this->cv.wait( lck, [this](){ return this->last != this->Get(); } );
    return this->Get();
  }
}
