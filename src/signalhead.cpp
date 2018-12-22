#include <sstream>

#include "signalhead.hpp"

namespace Signalbox {
  void SignalHead::RunSignal() {
    // First, unblock the thread which spawned the signal
    {
      // The mutex ensures that the spawning thread has
      // reached the cv.wait()
      std::lock_guard<std::mutex> lg(this->mtx);
      this->aspect = SignalAspect::Red;
      this->UpdatePinActivation( this->aspect );
    }
    this->cv.notify_one();

    // Slight risk of a race condition at this point
    // The invoking thread might set state Done
    // before the mutex is locked in the do loop
    // To guard against this, UpdatePinActivation
    // has to handle the Done state
    // This should only apply on the first time
    // through the loop; after that the mutex
    // and condition variable will handle things
    
    // Main loop
    bool isFlashOn = true;
    do {
      std::unique_lock<std::mutex> lck(this->mtx);
      auto endtimepoint = std::chrono::steady_clock::now() + this->flashInterval;
      
      this->savedFlash = this->flash;
      this->savedAspect = this->aspect;
      this->UpdatePinActivation( this->aspect );

      if( this->savedFlash == SignalFlash::Steady ) {
	this->TurnPinsOnOff( true );
	this->cv.wait( lck, [this](){return this->HaveUpdateOrDone();} );      
      } else {
	this->TurnPinsOnOff( isFlashOn );
	this->cv.wait_until( lck, endtimepoint, [this](){return this->HaveUpdateOrDone();} );
	isFlashOn = !isFlashOn;
      }
    } while( this->aspect != SignalAspect::Done );
  }
  
  void SignalHead::UpdatePinActivation( const SignalAspect a ) {
    // Flag everything as off
    for( auto it = this->pins.begin(); it!=this->pins.end(); ++it ) {
      it->second.isActive = false;
    }

    // Flag appropriate pins as on
    switch( a ) {
    case SignalAspect::Done: // From race condition in RunSignal
    case SignalAspect::Red:
      this->pins[SignalHeadPins::Red].isActive = true;
      break;
      
    case SignalAspect::Green:
      this->pins[SignalHeadPins::Green].isActive = true;
      break;
	  
    case SignalAspect::Yellow:
      this->pins[SignalHeadPins::Yellow1].isActive = true;
      break;
	
    case SignalAspect::DoubleYellow:
      this->pins[SignalHeadPins::Yellow1].isActive = true;
      this->pins[SignalHeadPins::Yellow2].isActive = true;
      break;
      
    default:
      std::stringstream errMsg;
      errMsg << __FUNCTION__ << ": Called with " << a;
      throw std::runtime_error(errMsg.str());
    }
  }

  void SignalHead::TurnPinsOnOff( const bool allowOn ) {
    for( auto it = this->pins.begin(); it!=this->pins.end(); ++it ) {
      auto p = &(it->second);
      if( allowOn && p->isActive ) {
	p->pin->TurnOn();
      } else {
	p->pin->TurnOff();
      }
    }
  }

  bool SignalHead::HaveUpdateOrDone() const {
    bool aspectChange = this->savedAspect != this->aspect;
    bool flashChange = this->savedFlash != this->flash;
    bool isDone = this->aspect == SignalAspect::Done;
    return aspectChange || flashChange || isDone;
  }
}
