#pragma once
#include <string>
#include <thread>

#include "digitalinputpin.hpp"

namespace Signalbox {
  class ConsolePinManager;

  class ConsoleDigitalInputPin : public DigitalInputPin {
  public:
    ConsoleDigitalInputPin() :
      DigitalInputPin(),
      state(false),
      id(),
      done(false),
      t() {
      this->t = std::thread(&ConsoleDigitalInputPin::Run, this);
    }

    ~ConsoleDigitalInputPin() {
      if( this->t.joinable() ) {
	this->done = true;
	this->t.join();
      }
    }
    
    virtual bool Get() const override;

    void Set(const bool level);

    void Run();
  private:
    friend class ConsolePinManager;

    bool state;
    std::string id;

    std::atomic<bool> done;
    std::thread t;
  };
}
