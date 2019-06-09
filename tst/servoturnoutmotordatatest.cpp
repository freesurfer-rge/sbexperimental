#include <boost/test/unit_test.hpp>

#include "mockpinmanagerfactory.hpp"
#include "mockrailtrafficcontrolclient.hpp"
#include "controlleditemmanager.hpp"

#include "servoturnoutmotordata.hpp"

BOOST_AUTO_TEST_SUITE( ServoTurnMotorData )

BOOST_AUTO_TEST_SUITE( GetErrors )

BOOST_AUTO_TEST_CASE( InvalidId )
{
  Signalbox::ServoTurnoutMotorData stmd;

  auto res = stmd.GetErrors();

  BOOST_REQUIRE_EQUAL( res.size(), 1 );
  const std::string expected("Invalid id");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( GetFactory )
{
  Signalbox::ServoTurnoutMotorData stmd;

  Signalbox::MockPinManagerFactory mpmf;
  std::shared_ptr<Signalbox::RailTrafficControlClient> mrtcc(new Signalbox::MockRailTrafficControlClient);
  Signalbox::ControlledItemManager cim(&mpmf, mrtcc);

  auto cif = stmd.GetFactory(&cim);
  BOOST_REQUIRE(cif);
  auto stmf = dynamic_cast<Signalbox::ServoTurnoutMotorFactory*>(cif);
  BOOST_REQUIRE(stmf);
  
}

BOOST_AUTO_TEST_SUITE_END()
