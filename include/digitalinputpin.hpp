#pragma once

#include <chrono>
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

    template<class Rep, class Period>
    bool WaitFor(const std::chrono::duration<Rep,Period>& waitTime ) {
      std::atomic<bool> last;
      std::unique_lock<std::mutex> lck(this->mtx);
      last = this->Get();
      this->cv.wait_for( lck,
			 waitTime,
			 [this,&last](){ return last != this->Get(); } );
      return this->Get();
    }
  protected:
    void NotifyOneUpdate();
    
  private:
    std::mutex mtx;
    std::condition_variable cv;
  };
}
