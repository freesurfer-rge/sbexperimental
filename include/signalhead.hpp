#pragma once
#include <memory>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "signalheadpins.hpp"
#include "signalheaddata.hpp"
#include "outputpin.hpp"
#include "signalstate.hpp"

namespace Signalbox {
  class SignalHead {
  public:
    ~SignalHead() {
      if( this->t.joinable() ) {
	this->SetState(SignalState::Done,false);
	this->t.join();
      }
    }
    
    ItemId getId() const {
      return this->id;
    }

    void Activate() {
      // Lock mutex before spawning the signal's thread
      std::unique_lock<std::mutex> lck(this->mtx);

      // Spawn the thread
      this->t = std::thread(&SignalHead::RunSignal, this);

      // Apparently, CVs can get spurious wakeups
      while( this->state == SignalState::Inactive ) {
	// Wait for the signal's thread to be ready
	this->cv.wait(lck);
      }
    }

    void RunSignal();

    void SetState(const SignalState s, const bool flashing) {
      if( (s == SignalState::Yellow) && (this->pins.size() < 3) ) {
	throw std::range_error("Not enough pins for Yellow");
      }
      if( (s == SignalState::DoubleYellow) && (this->pins.size() < 4) ) {
	throw std::range_error("Not enough pins for DoubleYellow");
      }

      {
	std::lock_guard<std::mutex> lg(this->mtx);
	this->state = s;
	this->flash = flashing;
      }
      this->cv.notify_one();
    }
    
    static std::unique_ptr<SignalHead> create( const SignalHeadData* sd ); 
  private:
    struct PinSwitch {
      bool isActive;
      std::unique_ptr<OutputPin> pin;

      PinSwitch() : isActive(false), pin() {}
      
      PinSwitch( bool a, std::unique_ptr<OutputPin> p ) : isActive(a), pin(std::move(p)) {}
    };
    
    ItemId id;
    SignalState state, savedState;
    bool flash, savedFlash;

    std::map<SignalHeadPins,PinSwitch> pins;

    std::thread t;
    std::mutex mtx;
    std::condition_variable cv;
    std::chrono::duration<int,std::milli> flashInterval;
    
    SignalHead(const ItemId sigId) :
      id(sigId),
      state(SignalState::Inactive), savedState(SignalState::Inactive),
      flash(false), savedFlash(false),
      pins(),
      t(),
      mtx(),
      cv(),
      flashInterval(std::chrono::seconds(1)) {}

    void UpdatePinActivation( const SignalState s );

    void TurnPinsOnOff( const bool allowOn );

    bool HaveUpdateOrDone() const;
  };
}
