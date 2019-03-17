#pragma once
#include <thread>
#include <atomic>
#include <chrono>

#include "controlleditem.hpp"

#include "digitalinputpin.hpp"
#include "railtrafficcontrolclient.hpp"

namespace Signalbox {
  class TrackCircuitMonitor : public ControlledItem {
  public:
    ~TrackCircuitMonitor() {
      this->Deactivate();
      if( this->t.joinable() ) {
	this->t.join();
      }
    }

    virtual void Activate() override;

    virtual void Deactivate() override;
    
    bool Get() const;

    void Run();

    RailTrafficControlClient* getClient() const {
      return this->rtc;
    }
    
    virtual std::string getTypeString() const override {
      return std::string("trackcircuitmonitor");
    }

    // Remove copy constructor and operator=
    TrackCircuitMonitor(const TrackCircuitMonitor&) = delete;
    TrackCircuitMonitor& operator=(const TrackCircuitMonitor&) = delete;
  private:
    friend class TrackCircuitMonitorFactory;

    TrackCircuitMonitor(const ItemId id) :
      ControlledItem(id),
      done(false),
      pin(),
      rtc(),
      pollInterval(std::chrono::seconds(2)),
      t() {}
    
    std::atomic<bool> done;
    DigitalInputPin* pin;
    RailTrafficControlClient* rtc;
    std::chrono::duration<int,std::milli> pollInterval;
    
    std::thread t;
  };
}
