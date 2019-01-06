#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>

namespace Signalbox {
  class DigitalInputPin {
  public:
    DigitalInputPin() :
      mtx(),
      cv(),
      last() {}
    
    virtual ~DigitalInputPin() {}

    virtual bool Get() const = 0;

    bool Wait();
  private:
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> last;
  };
}
