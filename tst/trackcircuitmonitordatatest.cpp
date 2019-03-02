#include <boost/test/unit_test.hpp>

#include "mockpinmanagerfactory.hpp"
#include "mockrailtrafficcontrolclient.hpp"
#include "controlleditemmanager.hpp"

#include "trackcircuitmonitordata.hpp"

BOOST_AUTO_TEST_SUITE( TrackCircuitMonitorData )

BOOST_AUTO_TEST_SUITE( GetErrors )

BOOST_AUTO_TEST_CASE( InvalidId )
{
  Signalbox::TrackCircuitMonitorData tcmd;

  auto res = tcmd.GetErrors();

  BOOST_REQUIRE_EQUAL( res.size(), 1 );
  const std::string expected("Invalid id");
  BOOST_CHECK_EQUAL( res.at(0).message, expected );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( GetFactory )
{
  Signalbox::TrackCircuitMonitorData tcmd;

  Signalbox::MockPinManagerFactory mpmf;
  std::shared_ptr<Signalbox::RailTrafficControlClient> mrtcc(new Signalbox::MockRailTrafficControlClient);
  Signalbox::ControlledItemManager cim(&mpmf, mrtcc);

  auto cif = tcmd.GetFactory(&cim);
  BOOST_REQUIRE(cif);
  auto tcmf = dynamic_cast<Signalbox::TrackCircuitMonitorFactory*>(cif);
  BOOST_REQUIRE(tcmf);
  
}
  
BOOST_AUTO_TEST_SUITE_END()
