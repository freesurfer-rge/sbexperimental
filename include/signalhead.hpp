#pragma once
#include <memory>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "signalheadpins.hpp"
#include "signalheaddata.hpp"
#include "pinmanager.hpp"
#include "digitaloutputpin.hpp"
#include "signalaspect.hpp"
#include "signalflash.hpp"

namespace Signalbox {
  class SignalHead {
  public:
    ~SignalHead() {
      if( this->t.joinable() ) {
	this->SetState(SignalAspect::Done,SignalFlash::Steady);
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
      while( this->aspect == SignalAspect::Inactive ) {
	// Wait for the signal's thread to be ready
	this->cv.wait(lck);
      }
    }

    void RunSignal();

    void SetState(const SignalAspect a, const SignalFlash f) {
      if( (a == SignalAspect::Yellow) && (this->pins.size() < 3) ) {
	throw std::range_error("Not enough pins for Yellow");
      }
      if( (a == SignalAspect::DoubleYellow) && (this->pins.size() < 4) ) {
	throw std::range_error("Not enough pins for DoubleYellow");
      }

      {
	std::lock_guard<std::mutex> lg(this->mtx);
	this->aspect = a;
	this->flash = f;
      }
      this->cv.notify_one();
    }
    
    static std::unique_ptr<SignalHead> create( const SignalHeadData* sd, PinManager* pm ); 
  private:
    struct PinSwitch {
      bool isActive;
      DigitalOutputPin* pin;

      PinSwitch() : isActive(false), pin(NULL) {}
      
      PinSwitch( bool a, DigitalOutputPin *p ) : isActive(a), pin(p) {}
    };
    
    ItemId id;
    SignalAspect aspect, savedAspect;
    SignalFlash flash, savedFlash;

    std::map<SignalHeadPins,PinSwitch> pins;

    std::thread t;
    std::mutex mtx;
    std::condition_variable cv;
    std::chrono::duration<int,std::milli> flashInterval;
    
    SignalHead(const ItemId sigId) :
      id(sigId),
      aspect(SignalAspect::Inactive), savedAspect(SignalAspect::Inactive),
      flash(SignalFlash::Steady), savedFlash(SignalFlash::Steady),
      pins(),
      t(),
      mtx(),
      cv(),
      flashInterval(std::chrono::seconds(1)) {}

    void UpdatePinActivation( const SignalAspect a );

    void TurnPinsOnOff( const bool allowOn );

    bool HaveUpdateOrDone() const;
  };
}
