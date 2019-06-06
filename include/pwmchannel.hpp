#pragma once

namespace Signalbox {
  class PWMChannel {
  public:
    virtual ~PWMChannel() {}

    virtual void Set(const int value) = 0;
  };
}
