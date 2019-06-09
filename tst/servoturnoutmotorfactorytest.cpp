#include <boost/test/unit_test.hpp>

#include "servoturnoutmotor.hpp"
#include "servoturnoutmotordata.hpp"

#include "servoturnoutmotorfactory.hpp"

// =========================================
#include "badcontrolleditemdata.hpp"
#include "mockpinmanagerfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( ServoTurnoutMotorFactory, MockPinManagerFixture )

BOOST_AUTO_TEST_CASE( Manufacture )
{
  Signalbox::ServoTurnoutMotorFactory stmf(&(this->mpm));

  Signalbox::ServoTurnoutMotorData stmd;
  const unsigned int straightVal = 10;
  const unsigned int curvedVal = 20;
  const std::string controller = "tstControl";
  const std::string controllerData = "tstControlData";
  stmd.id = Signalbox::ItemId::Random();
  stmd.straight = straightVal;
  stmd.curved = curvedVal;
  stmd.pwmChannelRequest.controller = controller;
  stmd.pwmChannelRequest.controllerData = controllerData;
  

  auto ci = stmf.Manufacture(&stmd);
  BOOST_REQUIRE(ci);
  BOOST_CHECK_EQUAL( ci->getId(), stmd.id );

  auto stm = dynamic_cast<Signalbox::ServoTurnoutMotor*>(ci.get());
  BOOST_REQUIRE(stm);

  // Check PWMChannel created
  BOOST_CHECK_EQUAL( this->mpm.PWMChannelCount(), 1 );
  auto pwmChannel = this->mpm.FetchMockPWMChannel(stmd.pwmChannelRequest);
  BOOST_REQUIRE(pwmChannel);

  BOOST_CHECK_EQUAL( controller, pwmChannel->controller );
  BOOST_CHECK_EQUAL( controllerData, pwmChannel->controllerData );
  BOOST_CHECK_EQUAL( straightVal, pwmChannel->Get() );

  BOOST_CHECK_EQUAL( Signalbox::TurnoutState::Straight, stm->getState() );

  BOOST_CHECK_EQUAL( stm->getTypeString(), "turnout" );
}

BOOST_AUTO_TEST_CASE( BadData )
{
  BadControlledItemData bd;

  Signalbox::ServoTurnoutMotorFactory tcmf(&(this->mpm));

  std::string msg("Failed to cast ControlledItemData to ServoTurnoutMotorData");
  BOOST_CHECK_EXCEPTION( tcmf.Manufacture(&bd),
			 std::runtime_error,
			 GetExceptionMessageChecker<std::runtime_error>(msg) );
}


BOOST_AUTO_TEST_SUITE_END()
