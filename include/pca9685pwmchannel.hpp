#pragma once

#include "pwmchannel.hpp"

namespace Signalbox {
  class PCA9685PWMChannel : public PWMChannel {
  public:
    PCA9685PWMChannel(const int pi,
		      const int devHandle,
		      const unsigned int stopReg) :
      piId(pi),
      deviceHandle(devHandle),
      stopRegister(stopReg) {}

    virtual void Set(const unsigned int value ) override;

    virtual unsigned int Get() const override;

    const int piId;
    const int deviceHandle;
    const unsigned int stopRegister;
  };
}
