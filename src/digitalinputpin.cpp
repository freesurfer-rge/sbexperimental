#include "digitalinputpin.hpp"

namespace Signalbox {
  bool DigitalInputPin::Wait() {
    std::atomic<bool> last;
    std::unique_lock<std::mutex> lck(this->mtx);
    last = this->Get();
    this->cv.wait( lck, [this,&last](){ return last != this->Get(); } );
    return this->Get();
  }

  void DigitalInputPin::NotifyOneUpdate() {
    std::lock_guard<std::mutex> lg(this->mtx);
    this->cv.notify_one();
  }
}
