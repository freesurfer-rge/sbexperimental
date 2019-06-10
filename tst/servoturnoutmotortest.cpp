#include <boost/test/unit_test.hpp>

#include "servoturnoutmotor.hpp"

#include "mockservoturnoutmotorfactoryfixture.hpp"

// No thread in the servoturnoutmotor (yet) so no need for pause

BOOST_FIXTURE_TEST_SUITE( ServoTurnoutMotor, MockServoTurnoutMotorFactoryFixture )

BOOST_AUTO_TEST_CASE( LifeCycle )
{
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
  BOOST_REQUIRE_NE( curvedVal, straightVal );

  auto stm = this->CreateServoTurnoutMotor(stmd);
  BOOST_REQUIRE( stm );

  BOOST_CHECK_EQUAL( this->mpm.PWMChannelCount(), 1 );

  stm->Activate();

  auto pwmChannel = this->mpm.FetchMockPWMChannel(stmd.pwmChannelRequest);
  BOOST_REQUIRE(pwmChannel);

  BOOST_CHECK_EQUAL( controller, pwmChannel->controller );
  BOOST_CHECK_EQUAL( controllerData, pwmChannel->controllerData );
  BOOST_CHECK_EQUAL( straightVal, pwmChannel->Get() );

  BOOST_CHECK_EQUAL( Signalbox::TurnoutState::Straight, stm->getState() );
}

BOOST_AUTO_TEST_CASE( SetCurvedAndStraight )
{
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
  BOOST_REQUIRE_NE( curvedVal, straightVal );

  auto stm = this->CreateServoTurnoutMotor(stmd);
  BOOST_REQUIRE( stm );

  BOOST_CHECK_EQUAL( this->mpm.PWMChannelCount(), 1 );

  stm->Activate();

  auto pwmChannel = this->mpm.FetchMockPWMChannel(stmd.pwmChannelRequest);
  BOOST_REQUIRE(pwmChannel);
  BOOST_CHECK_EQUAL( straightVal, pwmChannel->Get() );

  // Set to curved
  stm->SetState( Signalbox::TurnoutState::Curved );

  BOOST_CHECK_EQUAL( stm->getState(), Signalbox::TurnoutState::Curved );
  BOOST_CHECK_EQUAL( curvedVal, pwmChannel->Get() );

  // Set back to straight
  
  stm->SetState( Signalbox::TurnoutState::Straight );

  BOOST_CHECK_EQUAL( stm->getState(), Signalbox::TurnoutState::Straight );
  BOOST_CHECK_EQUAL( straightVal, pwmChannel->Get() );
}

BOOST_AUTO_TEST_SUITE_END()
