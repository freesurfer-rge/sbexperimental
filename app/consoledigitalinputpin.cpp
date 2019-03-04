#include <iostream>
#include <chrono>
#include <random>

#include "consoledigitalinputpin.hpp"

namespace Signalbox {
  bool ConsoleDigitalInputPin::Get() const {
    return this->state;
  }

  void ConsoleDigitalInputPin::Set(const bool level) {
    if( level ) {
      std::cout << "Input Pin : " << this->id << " ON" << std::endl;
    } else {
      std::cout << "Input Pin : " << this->id << " OFF" << std::endl;
    }
    this->state = level;
    this->NotifyOneUpdate();
  }

  void ConsoleDigitalInputPin::Run() {
    unsigned long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine rand(seed);
    std::uniform_int_distribution<int> dist(1, 4);

    while( !this->done ) {
      std::cout << "Pin " << this->id << " sleeping" << std::endl;
      const int sleepSecs = dist(rand);
      std::this_thread::sleep_for(std::chrono::seconds(sleepSecs));

      const bool nextSet = dist(rand) % 2 == 0;
      this->Set(nextSet);
    }
  }
}
