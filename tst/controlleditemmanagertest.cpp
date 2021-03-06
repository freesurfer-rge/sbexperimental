#include <boost/test/unit_test.hpp>

#include "controlleditemmanager.hpp"
#include "signalheaddata.hpp"
#include "signalhead.hpp"

#include "trackcircuitmonitordata.hpp"
#include "trackcircuitmonitor.hpp"

#include "mockpinmanager.hpp"

// =========================================
#include "mockpinmanagerfactoryfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( ControlledItemManager, MockPinManagerFactoryFixture )

// =========================================

BOOST_AUTO_TEST_SUITE( ControlledItemFactorySelector )

BOOST_AUTO_TEST_CASE( GetSignalHeadFactory )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);

  auto res = cim.GetSignalHeadFactory();
  BOOST_REQUIRE(res);

  auto shf = dynamic_cast<Signalbox::SignalHeadFactory*>(res);
  BOOST_REQUIRE(shf);
}

BOOST_AUTO_TEST_CASE( GetTrackCircuitMonitorFactory )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), this->rtcClient);

  auto res = cim.GetTrackCircuitMonitorFactory();
  BOOST_REQUIRE(res);

  auto tcmf = dynamic_cast<Signalbox::TrackCircuitMonitorFactory*>(res);
  BOOST_REQUIRE(tcmf);
}

BOOST_AUTO_TEST_SUITE_END()

// =========================================

BOOST_AUTO_TEST_SUITE( CreateItem )

BOOST_AUTO_TEST_CASE( CreateSignal )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);
  BOOST_REQUIRE_EQUAL( cim.GetAllItems().size(), 0 );
  
  const std::string redPin = "12";
  const std::string greenPin = "15";
  Signalbox::SignalHeadData sd;
  sd.aspectCount = 2;
  sd.id = Signalbox::ItemId::Random();
  sd.pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd.pinData[Signalbox::SignalHeadPins::Green] = greenPin;

  std::unique_ptr<Signalbox::ControlledItem> ci;
  ci = cim.CreateItem(&sd);
  BOOST_REQUIRE(ci);

  BOOST_CHECK_EQUAL( ci->getId(), sd.id );

  Signalbox::SignalHead *sig(NULL);
  sig = dynamic_cast<Signalbox::SignalHead*>(ci.get());
  BOOST_REQUIRE(sig);
 // Check both pins have been created
  BOOST_CHECK_EQUAL( this->mpmf.mpm->DigitalOutputPinCount(), 2 );

  // Red pin as expected - and on
  auto red = this->mpmf.mpm->FetchMockDigitalOutputPin(redPin);
  BOOST_REQUIRE( red );
  BOOST_CHECK( red->Get() );

  // Green pin as expected - and off
  auto green = this->mpmf.mpm->FetchMockDigitalOutputPin(greenPin);
  BOOST_REQUIRE( green );
  BOOST_CHECK( !green->Get() );
}

BOOST_AUTO_TEST_CASE( CreateTrackCircuitMonitor )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), this->rtcClient);
  BOOST_REQUIRE_EQUAL( cim.GetAllItems().size(), 0 );

  const std::string pinId = "GPIO26";
  Signalbox::TrackCircuitMonitorData tcmd;
  tcmd.id = Signalbox::ItemId::Random();
  tcmd.inputPin.id = pinId;
  tcmd.inputPin.settings["Setting"] = "Something";

  std::unique_ptr<Signalbox::ControlledItem> ci;
  ci = cim.CreateItem(&tcmd);
  BOOST_REQUIRE(ci);

  BOOST_CHECK_EQUAL( ci->getId(), tcmd.id );

  Signalbox::TrackCircuitMonitor* tcm(NULL);
  tcm = dynamic_cast<Signalbox::TrackCircuitMonitor*>(ci.get());
  BOOST_REQUIRE(tcm);

  // Check pin created
  BOOST_CHECK_EQUAL( this->mpmf.mpm->DigitalInputPinCount(), 1 );
  auto pin = this->mpmf.mpm->FetchMockDigitalInputPin(pinId);
  BOOST_REQUIRE( pin );
  BOOST_CHECK_EQUAL( pin->Get(), false );
  BOOST_CHECK_EQUAL( pin->createSettings.size(), 1 );
  BOOST_CHECK_EQUAL( pin->createSettings.at("Setting"), "Something" );

  BOOST_CHECK_EQUAL( tcm->Get(), false );
  BOOST_CHECK_EQUAL( tcm->getTypeString(), "trackcircuitmonitor" );
  BOOST_CHECK_EQUAL( tcm->getClient(), this->rtcClient.get() );
}

BOOST_AUTO_TEST_SUITE_END()

// =========================================

BOOST_AUTO_TEST_SUITE( PopulateItems )

BOOST_AUTO_TEST_CASE( SingleSignal )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);
  BOOST_REQUIRE_EQUAL( cim.GetAllItems().size(), 0 );

  std::vector<std::unique_ptr<Signalbox::ControlledItemData>> data;
  data.push_back(std::unique_ptr<Signalbox::SignalHeadData>(new Signalbox::SignalHeadData()));
  auto sd = dynamic_cast<Signalbox::SignalHeadData*>(data.at(0).get());
  BOOST_REQUIRE(sd);

  const std::string redPin = "10";
  const std::string greenPin = "12";
  sd->aspectCount = 2;
  sd->id = Signalbox::ItemId::Random();
  sd->pinData[Signalbox::SignalHeadPins::Red] = redPin;
  sd->pinData[Signalbox::SignalHeadPins::Green] = greenPin;

  auto res = cim.PopulateItems(data);
  BOOST_CHECK_EQUAL( res, 1 );

  auto items = cim.GetAllItems();
  BOOST_CHECK_EQUAL( items.size(), 1 );
  auto ci = items.at(0);
  BOOST_REQUIRE(ci);
  auto sh = dynamic_cast<Signalbox::SignalHead*>(ci);
  BOOST_CHECK_EQUAL( sh->getAspectCount(), 2 );
}

BOOST_AUTO_TEST_CASE( TwoSignals )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);

  std::vector<std::unique_ptr<Signalbox::ControlledItemData>> data;
  const int baseId = 123;
  for( int i=0; i<2; i++ ) {
    data.push_back(std::unique_ptr<Signalbox::SignalHeadData>(new Signalbox::SignalHeadData()));
    auto sd = dynamic_cast<Signalbox::SignalHeadData*>(data.at(i).get());
    BOOST_REQUIRE(sd);

    const std::string redPin = "10"+std::to_string(i);
    const std::string greenPin = "12"+std::to_string(i);
    sd->aspectCount = 2;
    sd->id = Signalbox::ItemId(baseId+i);
    sd->pinData[Signalbox::SignalHeadPins::Red] = redPin;
    sd->pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  }
  BOOST_REQUIRE_EQUAL( data.size(), 2 );
  
  auto res = cim.PopulateItems(data);
  BOOST_CHECK_EQUAL( res, 2 );
  BOOST_CHECK_EQUAL( cim.GetAllItems().size(), 2 );
}

BOOST_AUTO_TEST_CASE( DuplicateId )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);

  std::vector<std::unique_ptr<Signalbox::ControlledItemData>> data;
  const int duplicateId = 123;
  for( int i=0; i<2; i++ ) {
    data.push_back(std::unique_ptr<Signalbox::SignalHeadData>(new Signalbox::SignalHeadData()));
    auto sd = dynamic_cast<Signalbox::SignalHeadData*>(data.at(i).get());
    BOOST_REQUIRE(sd);

    const std::string redPin = "10"+std::to_string(i);
    const std::string greenPin = "12"+std::to_string(i);
    sd->aspectCount = 2;
    sd->id = Signalbox::ItemId(duplicateId);
    sd->pinData[Signalbox::SignalHeadPins::Red] = redPin;
    sd->pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  }
  BOOST_REQUIRE_EQUAL( data.size(), 2 );

  std::stringstream msg;
  msg << "Detected duplicate id: " << Signalbox::ItemId(duplicateId);
  BOOST_CHECK_EXCEPTION( cim.PopulateItems(data),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg.str()) );
}

BOOST_AUTO_TEST_SUITE_END()  

// =========================================

BOOST_AUTO_TEST_SUITE( ActivateItems )

BOOST_AUTO_TEST_CASE( TwoSignals )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);

  std::vector<std::unique_ptr<Signalbox::ControlledItemData>> data;
  const int baseId = 123;
  for( int i=0; i<2; i++ ) {
    data.push_back(std::unique_ptr<Signalbox::SignalHeadData>(new Signalbox::SignalHeadData()));
    auto sd = dynamic_cast<Signalbox::SignalHeadData*>(data.at(i).get());
    BOOST_REQUIRE(sd);

    const std::string redPin = "10"+std::to_string(i);
    const std::string greenPin = "12"+std::to_string(i);
    sd->aspectCount = 2;
    sd->id = Signalbox::ItemId(baseId+i);
    sd->pinData[Signalbox::SignalHeadPins::Red] = redPin;
    sd->pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  }
  BOOST_REQUIRE_EQUAL( data.size(), 2 );
  
  auto pop = cim.PopulateItems(data);
  BOOST_CHECK_EQUAL( pop, 2 );

  auto res = cim.ActivateItems();
  BOOST_CHECK_EQUAL( res, 2 );
  
  BOOST_CHECK_EQUAL( cim.GetAllItems().size(), 2 );
}

BOOST_AUTO_TEST_CASE( OneOfEach )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), this->rtcClient);
  BOOST_REQUIRE_EQUAL( cim.GetAllItems().size(), 0 );

  const Signalbox::ItemId sigId = Signalbox::ItemId::Random();
  const Signalbox::ItemId tcmId = Signalbox::ItemId(sigId.Get()+1);
  BOOST_REQUIRE_NE( sigId, tcmId );
  
  std::vector<std::unique_ptr<Signalbox::ControlledItemData>> data;
  
  {
    const std::string pinId = "GPIO26";
    std::unique_ptr<Signalbox::TrackCircuitMonitorData> tcmd( new Signalbox::TrackCircuitMonitorData );
    tcmd->id = tcmId;
    tcmd->inputPin.id = pinId;

    data.push_back(std::move(tcmd));
  }

  {
    std::unique_ptr<Signalbox::SignalHeadData> sd( new Signalbox::SignalHeadData );

    sd->aspectCount = 3;
    sd->id = sigId;
    sd->pinData[Signalbox::SignalHeadPins::Red] = "GPIO01";
    sd->pinData[Signalbox::SignalHeadPins::Yellow1] = "GPIO02";
    sd->pinData[Signalbox::SignalHeadPins::Green] = "GPIO03";
    
    data.push_back(std::move(sd));
  }

  BOOST_REQUIRE_EQUAL( data.size(), 2 );
  
  bool gotSignalHead = false;
  bool gotTrackCircuitMonitor = false;

  auto pop = cim.PopulateItems(data);
  BOOST_CHECK_EQUAL( pop, 2 );

  auto res = cim.ActivateItems();
  BOOST_CHECK_EQUAL( res, 2 );

  auto items = cim.GetAllItems();
  BOOST_CHECK_EQUAL( items.size(), 2 );

  for( auto it = items.begin(); it!=items.end(); ++it ) {
    auto ci = *it;
    BOOST_REQUIRE(ci);

    auto sh = dynamic_cast<Signalbox::SignalHead*>(ci);
    auto tcm = dynamic_cast<Signalbox::TrackCircuitMonitor*>(ci);

    if( sh != nullptr ) {
      gotSignalHead = true;
      BOOST_CHECK_EQUAL( sh->getId(), sigId );
    } else if( tcm != nullptr ) {
      gotTrackCircuitMonitor = true;
      BOOST_CHECK_EQUAL( tcm->getId(), tcmId );
    } else {
      BOOST_FAIL("Unrecognised item");
    }
  }
  
  BOOST_CHECK( gotSignalHead );
  BOOST_CHECK( gotTrackCircuitMonitor );
}
  
BOOST_AUTO_TEST_SUITE_END()

// =========================================

BOOST_AUTO_TEST_SUITE( GetById )

BOOST_AUTO_TEST_CASE( GetTwoItems )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);

  std::vector<std::unique_ptr<Signalbox::ControlledItemData>> data;
  const int baseId = 123;
  const std::string redPinBase = "18";
  const std::string greenPinBase = "02";
  for( int i=0; i<2; i++ ) {
    data.push_back(std::unique_ptr<Signalbox::SignalHeadData>(new Signalbox::SignalHeadData()));
    auto sd = dynamic_cast<Signalbox::SignalHeadData*>(data.at(i).get());
    BOOST_REQUIRE(sd);

    const std::string redPin = redPinBase+std::to_string(i);
    const std::string greenPin = greenPinBase+std::to_string(i);
    sd->aspectCount = 2;
    sd->id = Signalbox::ItemId(baseId+i);
    sd->pinData[Signalbox::SignalHeadPins::Red] = redPin;
    sd->pinData[Signalbox::SignalHeadPins::Green] = greenPin;
  }
  BOOST_REQUIRE_EQUAL( data.size(), 2 );
  
  auto res = cim.PopulateItems(data);
  BOOST_CHECK_EQUAL( res, 2 );
  BOOST_CHECK_EQUAL( cim.GetAllItems().size(), 2 );

  for( int i=0; i<2; i++ ) {
    Signalbox::ItemId target(baseId+i);

    auto ci = cim.GetById(target);
    BOOST_REQUIRE(ci);
    BOOST_CHECK_EQUAL( ci->getId(), target );

    auto sh = dynamic_cast<Signalbox::SignalHead*>(ci);
    BOOST_REQUIRE(sh);
  }
}

BOOST_AUTO_TEST_CASE( GetNonExistant )
{
  Signalbox::ControlledItemManager cim(&(this->mpmf), nullptr);
  BOOST_CHECK_EQUAL( cim.GetAllItems().size(), 0 );

  const Signalbox::ItemId anyId(10);

  std::stringstream msg;
  msg << "Item not found: " << anyId;
  BOOST_CHECK_EXCEPTION( cim.GetById(anyId),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg.str()) );
  BOOST_CHECK_EQUAL( cim.GetAllItems().size(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE_END()
