#include <sstream>

#include "signalhead.hpp"

namespace Signalbox {
  void SignalHead::RunSignal() {
    // First, unblock the thread which spawned the signal
    {
      // The mutex ensures that the spawning thread has
      // reached the cv.wait()
      std::lock_guard<std::mutex> lg(this->mtx);
      this->state = SignalState::Red;
      this->UpdatePinActivation( this->state );
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
      this->savedState = this->state;
      this->UpdatePinActivation( this->state );

      if( !this->savedFlash ) {
	this->TurnPinsOnOff( true );
	this->cv.wait( lck, [this](){return this->HaveUpdateOrDone();} );      
      } else {
	this->TurnPinsOnOff( isFlashOn );
	this->cv.wait_until( lck, endtimepoint, [this](){return this->HaveUpdateOrDone();} );
	isFlashOn = !isFlashOn;
      }
    } while( this->state != SignalState::Done );
  }
  
  void SignalHead::UpdatePinActivation( const SignalState s ) {
    // Flag everything as off
    for( auto it = this->pins.begin(); it!=this->pins.end(); ++it ) {
      it->second.isActive = false;
    }

    // Flag appropriate pins as on
    switch( s ) {
    case SignalState::Done: // From race condition in RunSignal
    case SignalState::Red:
      this->pins[SignalHeadPins::Red].isActive = true;
      break;
      
    case SignalState::Green:
      this->pins[SignalHeadPins::Green].isActive = true;
      break;
	  
    case SignalState::Yellow:
      this->pins[SignalHeadPins::Yellow1].isActive = true;
      break;
	
    case SignalState::DoubleYellow:
      this->pins[SignalHeadPins::Yellow1].isActive = true;
      this->pins[SignalHeadPins::Yellow2].isActive = true;
      break;
      
    default:
      std::stringstream errMsg;
      errMsg << __FUNCTION__ << ": Called with " << s;
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
    bool stateChange = this->savedState != this->state;
    bool flashChange = this->savedFlash != this->flash;
    bool isDone = this->state == SignalState::Done;
    return stateChange || flashChange || isDone;
  }
  
  std::unique_ptr<SignalHead> SignalHead::create( const SignalHeadData* sd ) {
    // Skip input validation for now

    std::unique_ptr<SignalHead> res;
    res.reset( new SignalHead(sd->id) );

    // Add pins
    for( auto it=sd->pinData.begin(); it!=sd->pinData.end(); ++it ) {
      auto aspect = (*it).first;
      auto pinId = (*it).second;
      res->pins[aspect] = PinSwitch(false, OutputPin::create(pinId));
      res->pins[aspect].pin->TurnOff();
    }
    // Turn red on
    auto p = &res->pins[SignalHeadPins::Red];
    p->isActive = true;
    p->pin->TurnOn();
    
    return res;
  }
}
