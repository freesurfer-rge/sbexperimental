#include <boost/test/unit_test.hpp>

#include "controlleditemmanager.hpp"

#include "mockpinmanager.hpp"

// =========================================
#include "mockpinmanagerfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( ControlledItemManager, MockPinManagerFixture )

// =========================================

BOOST_AUTO_TEST_SUITE( ControlledItemFactorySelector )

BOOST_AUTO_TEST_CASE( GetSignalHeadFactory )
{
  Signalbox::ControlledItemManager cim(this->pm);

  auto res = cim.GetSignalHeadFactory();
  BOOST_REQUIRE(res);

  auto shf = dynamic_cast<Signalbox::SignalHeadFactory*>(res);
  BOOST_REQUIRE(shf);
}

BOOST_AUTO_TEST_SUITE_END()

// =========================================

BOOST_AUTO_TEST_SUITE_END()
