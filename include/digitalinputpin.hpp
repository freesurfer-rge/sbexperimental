#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>

namespace Signalbox {
  class DigitalInputPin {
  public:
    DigitalInputPin() :
      mtx(),
      cv() {}
    
    virtual ~DigitalInputPin() {}

    virtual bool Get() const = 0;

    bool Wait();

  protected:
    void NotifyOneUpdate();
    
  private:
    std::mutex mtx;
    std::condition_variable cv;
  };
}
