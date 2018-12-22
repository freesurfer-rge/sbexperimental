#include <boost/test/unit_test.hpp>

#include "signalhead.hpp"

#include "mocksignalheadfactoryfixture.hpp"

// =========================================

void PauseForSignal() {
  // The signal state is updated by another thread and
  // we do not have visibility in to it
  // Wait a short time to allow for updates before
  // performing checks
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// =========================================

BOOST_FIXTURE_TEST_SUITE( SignalHead, MockSignalHeadFactoryFixture )

// =========================================

BOOST_AUTO_TEST_SUITE(SteadyAspects)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const std::string redPin = "15";
  const std::string greenPin = "12";
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = this->CreateSignal(sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( this->mpm.DigitalOutputPinCount(), 2 );

  // Red pin as expected - and on
  auto red = this->mpm.FetchMockDigitalOutputPin(redPin);
  BOOST_REQUIRE( red );
  BOOST_CHECK( red->Get() );

  // Green pin as expected - and off
  auto green = this->mpm.FetchMockDigitalOutputPin(greenPin);
  BOOST_REQUIRE( green );
  BOOST_CHECK( !green->Get() );
  
  // Activate the signal
  sig->Activate();

  // Verify we're still in the right state
  BOOST_CHECK( red->Get() );
  BOOST_CHECK( !green->Get() );
  
  // Change signal to steady green
  sig->SetState(Signalbox::SignalAspect::Green, Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( !red->Get() );
  BOOST_CHECK( green->Get() );

  // Change back to steady Red
  sig->SetState(Signalbox::SignalAspect::Red, Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( red->Get() );
  BOOST_CHECK( !green->Get() );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  const std::string redPin = "GPIO01";
  const std::string yellow1Pin = "GPIO02";
  const std::string greenPin = "GPIO03";

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 3;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = this->CreateSignal(sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( this->mpm.DigitalOutputPinCount(), 3 );

  // Red pin as expected - and on
  auto red = this->mpm.FetchMockDigitalOutputPin(redPin);
  BOOST_REQUIRE( red );
  BOOST_CHECK( red->Get() );

  // Yellow1 pin as expected - and off
  auto yellow1 = this->mpm.FetchMockDigitalOutputPin(yellow1Pin);
  BOOST_REQUIRE( yellow1 );
  BOOST_CHECK( !yellow1->Get() );
  
  // Green pin as expected - and off
  auto green = this->mpm.FetchMockDigitalOutputPin(greenPin);
  BOOST_REQUIRE( green );
  BOOST_CHECK( !green->Get() );

  // Activate the signal
  sig->Activate();

  // Verify we're still in the right state
  BOOST_CHECK( red->Get() );
  BOOST_CHECK( !yellow1->Get() );
  BOOST_CHECK( !green->Get() );

  // Set steady yellow
  sig->SetState(Signalbox::SignalAspect::Yellow, Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( !red->Get() );
  BOOST_CHECK( yellow1->Get() );
  BOOST_CHECK( !green->Get() );

  // Set steady green
  sig->SetState(Signalbox::SignalAspect::Green, Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( !red->Get() );
  BOOST_CHECK( !yellow1->Get() );
  BOOST_CHECK( green->Get() );

  // Back to steady red
  sig->SetState(Signalbox::SignalAspect::Red, Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( red->Get() );
  BOOST_CHECK( !yellow1->Get() );
  BOOST_CHECK( !green->Get() );
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  const std::string redPin = "1";
  const std::string yellow1Pin = "2";
  const std::string yellow2Pin = "7";
  const std::string greenPin = "3";

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 4;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow2] = yellow2Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = this->CreateSignal(sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( this->mpm.DigitalOutputPinCount(), 4 );

  // Red pin as expected - and on
  auto red = this->mpm.FetchMockDigitalOutputPin(redPin);
  BOOST_REQUIRE( red );
  BOOST_CHECK( red->Get() );

  // Yellow1 pin as expected - and off
  auto yellow1 = this->mpm.FetchMockDigitalOutputPin(yellow1Pin);
  BOOST_REQUIRE( yellow1 );
  BOOST_CHECK( !yellow1->Get() );
  
  // Yellow2 pin as expected - and off
  auto yellow2 = this->mpm.FetchMockDigitalOutputPin(yellow2Pin);
  BOOST_REQUIRE( yellow2 );
  BOOST_CHECK( !yellow2->Get() );
  
  // Green pin as expected - and off
  auto green = this->mpm.FetchMockDigitalOutputPin(greenPin);
  BOOST_REQUIRE( green );
  BOOST_CHECK( !green->Get() );
  
  // Activate the signal
  sig->Activate();

  // Verify we're still in the right state
  BOOST_CHECK( red->Get() );
  BOOST_CHECK( !yellow1->Get() );
  BOOST_CHECK( !yellow2->Get() );
  BOOST_CHECK( !green->Get() );
  
  // Set steady yellow
  sig->SetState(Signalbox::SignalAspect::Yellow, Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( !red->Get() );
  BOOST_CHECK( yellow1->Get() );
  BOOST_CHECK( !yellow2->Get() );
  BOOST_CHECK( !green->Get() );

  // Set steady double yellow
  sig->SetState(Signalbox::SignalAspect::DoubleYellow, Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( !red->Get() );
  BOOST_CHECK( yellow1->Get() );
  BOOST_CHECK( yellow2->Get() );
  BOOST_CHECK( !green->Get() );

  // Set steady green
  sig->SetState(Signalbox::SignalAspect::Green,Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( !red->Get() );
  BOOST_CHECK( !yellow1->Get() );
  BOOST_CHECK( !yellow2->Get() );
  BOOST_CHECK( green->Get() );

  // Back to steady red
  sig->SetState(Signalbox::SignalAspect::Red,Signalbox::SignalFlash::Steady);
  PauseForSignal();
  BOOST_CHECK( red->Get() );
  BOOST_CHECK( !yellow1->Get() );
  BOOST_CHECK( !yellow2->Get() );
  BOOST_CHECK( !green->Get() );
}

BOOST_AUTO_TEST_SUITE_END()

// ==============================================================

BOOST_AUTO_TEST_SUITE(FlashingAspects)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const std::string redPin = "GPIO05";
  const std::string greenPin = "GPIO18";
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = this->CreateSignal(sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( this->mpm.DigitalOutputPinCount(), 2 );

  // Red pin as expected - and on
  auto red = this->mpm.FetchMockDigitalOutputPin(redPin);
  BOOST_REQUIRE( red );
  BOOST_CHECK( red->Get() );

  // Green pin as expected - and off
  auto green = this->mpm.FetchMockDigitalOutputPin(greenPin);
  BOOST_REQUIRE( green );
  BOOST_CHECK( !green->Get() );
  
  BOOST_TEST_CHECKPOINT("Initialisation complete");
  
  // Activate the signal
  sig->Activate();

  // Hard to do checks on the flashes, since we have no
  // access to the internal state
  // The following are imprecise

  bool seenGreenOn = false;
  bool seenGreenOff = false;
  bool seenRedOn = false;
  bool seenRedOff = false;

  auto checkInterval = std::chrono::milliseconds(50);
  auto checkForTime = std::chrono::seconds(2);
  
  // Set to flashing green
  sig->SetState(Signalbox::SignalAspect::Green, Signalbox::SignalFlash::Flashing);
  PauseForSignal();
  auto start = std::chrono::system_clock::now();
  do {
    if( green->Get() ) {
      seenGreenOn = true;
    } else {
      seenGreenOff = true;
    }

    if( red->Get() ) {
      seenRedOn = true;
    } else {
      seenRedOff = true;
    }
    std::this_thread::sleep_for(checkInterval);
  } while( std::chrono::system_clock::now() - start < checkForTime );
  BOOST_CHECK( seenGreenOff );
  BOOST_CHECK( seenGreenOn );
  BOOST_CHECK( seenRedOff );
  BOOST_CHECK( !seenRedOn );

  BOOST_TEST_CHECKPOINT("Flashing green complete");
  
  // And flashing red
  seenGreenOn = seenGreenOff = seenRedOn = seenRedOff = false;
  sig->SetState(Signalbox::SignalAspect::Red, Signalbox::SignalFlash::Flashing);
  PauseForSignal();
  start = std::chrono::system_clock::now();
  do {
    if( green->Get() ) {
      seenGreenOn = true;
    } else {
      seenGreenOff = true;
    }

    if( red->Get() ) {
      seenRedOn = true;
    } else {
      seenRedOff = true;
    }
    std::this_thread::sleep_for(checkInterval);
  } while( std::chrono::system_clock::now() - start < checkForTime );
  BOOST_CHECK( seenGreenOff );
  BOOST_CHECK( !seenGreenOn );
  BOOST_CHECK( seenRedOff );
  BOOST_CHECK( seenRedOn );
}
  
BOOST_AUTO_TEST_SUITE_END()

// =================================

BOOST_AUTO_TEST_SUITE(SetStateErrors)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const char redPin = 15;
  const char greenPin = 12;
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = this->CreateSignal(sd);
  BOOST_REQUIRE( sig );

  BOOST_TEST_CHECKPOINT("Signal constructed");
  
  // Activate the signal
  sig->Activate();

  // Attempt to set incorrect aspects
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalAspect::Yellow, Signalbox::SignalFlash::Steady),
		     std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalAspect::Yellow, Signalbox::SignalFlash::Flashing),
		     std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalAspect::DoubleYellow, Signalbox::SignalFlash::Steady),
		     std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalAspect::DoubleYellow, Signalbox::SignalFlash::Flashing),
		     std::range_error );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  const char redPin = 3;
  const char yellow1Pin = 2;
  const char greenPin = 1;

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 3;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = this->CreateSignal(sd);
  BOOST_REQUIRE( sig );

  // Activate the signal
  sig->Activate();

  // Attempt to set incorrect aspects
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalAspect::DoubleYellow, Signalbox::SignalFlash::Steady),
		     std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalAspect::DoubleYellow, Signalbox::SignalFlash::Flashing),
		     std::range_error );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
