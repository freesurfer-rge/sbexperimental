#include <boost/test/unit_test.hpp>

#include "mockdigitalinputpin.hpp"

// =========================================
#include "mockpinmanagerfixture.hpp"
#include "exceptionmessagecheck.hpp"
// =========================================

BOOST_FIXTURE_TEST_SUITE( MockDigitalInputPin, MockPinManagerFixture )

BOOST_AUTO_TEST_CASE( GetAndSet )
{
  const std::string anyId = "AnyId";

  auto dip = this->pm->CreateDigitalInputPin(anyId);
  BOOST_REQUIRE(dip);

  auto mdip = dynamic_cast<Signalbox::MockDigitalInputPin*>(dip);
  BOOST_REQUIRE(mdip);

  BOOST_CHECK_EQUAL( mdip->Get(), false );
  mdip->Set(true);
  BOOST_CHECK_EQUAL( mdip->Get(), true );
  mdip->Set(false);
  BOOST_CHECK_EQUAL( mdip->Get(), false);
}

BOOST_AUTO_TEST_SUITE_END()
