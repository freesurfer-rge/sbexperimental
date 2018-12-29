#include <boost/test/unit_test.hpp>

#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "signalheadfactory.hpp"

// =========================================
#include "mockpinmanagerfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( SignalHeadFactory, MockPinManagerFixture )

BOOST_AUTO_TEST_CASE( TwoAspect )
{
  Signalbox::SignalHeadFactory shf(&(this->mpm));

  const std::string redPin = "12";
  const std::string greenPin = "15";
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::ControlledItem> ci;
  ci = shf.Manufacture(&sd);
  BOOST_REQUIRE(ci);
  BOOST_CHECK_EQUAL( ci->getId(), sd.id );

  Signalbox::SignalHead *sig(NULL);
  sig = dynamic_cast<Signalbox::SignalHead*>(ci.get());
  BOOST_REQUIRE(sig);
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

  BOOST_CHECK_EQUAL( sig->getAspectCount(), 2 );
  BOOST_CHECK_EQUAL( sig->getAspect(), Signalbox::SignalAspect::Inactive );
  BOOST_CHECK_EQUAL( sig->getFlash(), Signalbox::SignalFlash::Steady );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  Signalbox::SignalHeadFactory shf(&(this->mpm));

  const std::string redPin = "GPIO01";
  const std::string yellow1Pin = "GPIO02";
  const std::string greenPin = "GPIO03";

  Signalbox::SignalHeadData sd;
  sd.aspectCount = 3;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Yellow1] = yellow1Pin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  
  std::unique_ptr<Signalbox::ControlledItem> ci;
  ci = shf.Manufacture(&sd);
  BOOST_REQUIRE(ci);
  BOOST_CHECK_EQUAL( ci->getId(), sd.id );

  Signalbox::SignalHead *sig(NULL);
  sig = dynamic_cast<Signalbox::SignalHead*>(ci.get());
  BOOST_REQUIRE(sig);
 // Check all pins have been created
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

  BOOST_CHECK_EQUAL( sig->getAspectCount(), 3 );
  BOOST_CHECK_EQUAL( sig->getAspect(), Signalbox::SignalAspect::Inactive );
  BOOST_CHECK_EQUAL( sig->getFlash(), Signalbox::SignalFlash::Steady );
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  Signalbox::SignalHeadFactory shf(&(this->mpm));

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
   
  std::unique_ptr<Signalbox::ControlledItem> ci;
  ci = shf.Manufacture(&sd);
  BOOST_REQUIRE(ci);
  BOOST_CHECK_EQUAL( ci->getId(), sd.id );

  Signalbox::SignalHead *sig(NULL);
  sig = dynamic_cast<Signalbox::SignalHead*>(ci.get());
  BOOST_REQUIRE(sig);

  // Check all pins have been created
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

  BOOST_CHECK_EQUAL( sig->getAspectCount(), 4 );
  BOOST_CHECK_EQUAL( sig->getAspect(), Signalbox::SignalAspect::Inactive );
  BOOST_CHECK_EQUAL( sig->getFlash(), Signalbox::SignalFlash::Steady );
}


BOOST_AUTO_TEST_CASE( BadData )
{
  class BadData : public Signalbox::ControlledItemData {
  public:
    virtual std::vector<Signalbox::ControlledItemDataError> GetErrors() const override {
      return std::vector<Signalbox::ControlledItemDataError>();
    }

    virtual Signalbox::ControlledItemFactory* GetFactory(Signalbox::ControlledItemFactorySelector* factorySelector) const override {
      BOOST_WARN( factorySelector );
      throw std::runtime_error("BadData::GetFactory Not Implemented!");
    }
  };
  
  BadData bd;

  Signalbox::SignalHeadFactory shf(&(this->mpm));

  std::string msg("Failed to cast ControlledItemData to SignalHeadData");
  BOOST_CHECK_EXCEPTION( shf.Manufacture(&bd),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
