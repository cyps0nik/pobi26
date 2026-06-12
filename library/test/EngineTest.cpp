#include <boost/test/unit_test.hpp>
#include "model/Engine.h"
#include <stdexcept>

struct EngineFixture {
    int displacement = 1500;
    FuelType fuel = Petrol;
};

BOOST_FIXTURE_TEST_SUITE(EngineTest, EngineFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGetters) {
    Engine eng(displacement, fuel);
    BOOST_TEST(eng.getEngineDisplacement() == displacement);
    BOOST_TEST(eng.getFuelType() == fuel);
    BOOST_TEST(eng.getMultiplier() == 1.25);
}

BOOST_AUTO_TEST_CASE(Exceptions) {
    BOOST_REQUIRE_THROW(Engine(-100, fuel), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()