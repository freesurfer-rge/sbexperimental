#include <boost/test/unit_test.hpp>

#include "signalhead.hpp"

#include "mockoutputpinfixture.hpp"

// =========================================

void PauseForSignal() {
  // The signal state is updated by another thread and
  // we do not have visibility in to it
  // Wait a short time to allow for updates before
  // performing checks
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// =========================================


BOOST_FIXTURE_TEST_SUITE( SignalHead, MockOutputPinFixture )

// =========================================

BOOST_AUTO_TEST_SUITE( Creation )

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const char redPin = 12;
  const char greenPin = 15;
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 2 );

  // Red pin as expected - and on
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[redPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[redPin]->pin, redPin );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );

  // Green pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[greenPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[greenPin]->pin, greenPin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  const char redPin = 1;
  const char yellow1Pin = 2;
  const char greenPin = 3;

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 3;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 3 );

  
  // Red pin as expected - and on
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[redPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[redPin]->pin, redPin );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );

  // Yellow1 pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[yellow1Pin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[yellow1Pin]->pin, yellow1Pin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  
  // Green pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[greenPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[greenPin]->pin, greenPin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  const char redPin = 1;
  const char yellow1Pin = 2;
  const char yellow2Pin = 7;
  const char greenPin = 3;

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 4;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow2] = yellow2Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 4 );
  
  // Red pin as expected - and on
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[redPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[redPin]->pin, redPin );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );

  // Yellow1 pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[yellow1Pin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[yellow1Pin]->pin, yellow1Pin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  
  // Yellow1 pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[yellow2Pin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[yellow2Pin]->pin, yellow2Pin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow2Pin]->isOn );
  
  // Green pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[greenPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[greenPin]->pin, greenPin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );
}

BOOST_AUTO_TEST_SUITE_END()

// =========================================

BOOST_AUTO_TEST_SUITE(SteadyAspects)

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
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 2 );

  // Red pin as expected - and on
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[redPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[redPin]->pin, redPin );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );

  // Green pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[greenPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[greenPin]->pin, greenPin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Activate the signal
  sig->Activate();

  // Verify we're still in the right state
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Change signal to steady green
  sig->SetState(Signalbox::SignalState::Green,false);
  PauseForSignal();
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Change back to steady Red
  sig->SetState(Signalbox::SignalState::Red,false);
  PauseForSignal();
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  const char redPin = 1;
  const char yellow1Pin = 2;
  const char greenPin = 3;

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 3;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 3 );
  
  // Red pin as expected - and on
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[redPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[redPin]->pin, redPin );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );

  // Yellow1 pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[yellow1Pin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[yellow1Pin]->pin, yellow1Pin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  
  // Green pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[greenPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[greenPin]->pin, greenPin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Activate the signal
  sig->Activate();

  // Verify we're still in the right state
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Set steady yellow
  sig->SetState(Signalbox::SignalState::Yellow,false);
  PauseForSignal();
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Set steady green
  sig->SetState(Signalbox::SignalState::Green,false);
  PauseForSignal();
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Back to steady red
  sig->SetState(Signalbox::SignalState::Red,false);
  PauseForSignal();
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  const char redPin = 1;
  const char yellow1Pin = 2;
  const char yellow2Pin = 7;
  const char greenPin = 3;

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 4;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow2] = yellow2Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 4 );
  
  // Red pin as expected - and on
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[redPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[redPin]->pin, redPin );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );

  // Yellow1 pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[yellow1Pin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[yellow1Pin]->pin, yellow1Pin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  
  // Yellow1 pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[yellow2Pin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[yellow2Pin]->pin, yellow2Pin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow2Pin]->isOn );
  
  // Green pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[greenPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[greenPin]->pin, greenPin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Activate the signal
  sig->Activate();

  // Verify we're still in the right state
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow2Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );
  
  // Set steady yellow
  sig->SetState(Signalbox::SignalState::Yellow,false);
  PauseForSignal();
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow2Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Set steady double yellow
  sig->SetState(Signalbox::SignalState::DoubleYellow,false);
  PauseForSignal();
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[yellow2Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Set steady green
  sig->SetState(Signalbox::SignalState::Green,false);
  PauseForSignal();
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow2Pin]->isOn );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[greenPin]->isOn );

  // Back to steady red
  sig->SetState(Signalbox::SignalState::Red,false);
  PauseForSignal();
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow1Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[yellow2Pin]->isOn );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FlashingAspects)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const char redPin = 5;
  const char greenPin = 18;
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::SignalHead> sig;
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );
  BOOST_CHECK_EQUAL( sig->getId(), sd.id );

  // Check both pins have been created
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins.size(), 2 );

  // Red pin as expected - and on
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[redPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[redPin]->pin, redPin );
  BOOST_CHECK( Signalbox::MockOutputPin::allPins[redPin]->isOn );

  // Green pin as expected - and off
  BOOST_REQUIRE( Signalbox::MockOutputPin::allPins[greenPin] );
  BOOST_CHECK_EQUAL( Signalbox::MockOutputPin::allPins[greenPin]->pin, greenPin );
  BOOST_CHECK( !Signalbox::MockOutputPin::allPins[greenPin]->isOn );

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
  sig->SetState(Signalbox::SignalState::Green, true);
  PauseForSignal();
  auto start = std::chrono::system_clock::now();
  do {
    if( Signalbox::MockOutputPin::allPins[greenPin]->isOn ) {
      seenGreenOn = true;
    } else {
      seenGreenOff = true;
    }

    if( Signalbox::MockOutputPin::allPins[redPin]->isOn ) {
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
  sig->SetState(Signalbox::SignalState::Red, true);
  PauseForSignal();
  start = std::chrono::system_clock::now();
  do {
    if( Signalbox::MockOutputPin::allPins[greenPin]->isOn ) {
      seenGreenOn = true;
    } else {
      seenGreenOff = true;
    }

    if( Signalbox::MockOutputPin::allPins[redPin]->isOn ) {
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
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );

  BOOST_TEST_CHECKPOINT("Signal constructed");
  
  // Activate the signal
  sig->Activate();

  // Attempt to set incorrect aspects
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalState::Yellow,false), std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalState::Yellow,true), std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalState::DoubleYellow,false), std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalState::DoubleYellow,true), std::range_error );
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
  sig = Signalbox::SignalHead::create(&sd);
  BOOST_REQUIRE( sig );

  // Activate the signal
  sig->Activate();

  // Attempt to set incorrect aspects
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalState::DoubleYellow,false), std::range_error );
  BOOST_CHECK_THROW( sig->SetState(Signalbox::SignalState::DoubleYellow,true), std::range_error );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
