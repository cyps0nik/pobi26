#include <boost/test/unit_test.hpp>
#include "model/Accumulator.h"
#include <stdexcept>

struct AccumulatorFixture {
    int capacity = 50;
    int degradation = 10;
};

BOOST_FIXTURE_TEST_SUITE(AccumulatorTest, AccumulatorFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGetters) {
    Accumulator acc(capacity, degradation);
    BOOST_TEST(acc.getCapacityKWh() == capacity);
    BOOST_TEST(acc.getDegradationLevel() == degradation);
    BOOST_TEST(acc.getMultiplier() == 1.1333333333333333, boost::test_tools::tolerance(0.001));
}

BOOST_AUTO_TEST_CASE(Exceptions) {
    BOOST_REQUIRE_THROW(Accumulator(-10, degradation), std::invalid_argument);
    BOOST_REQUIRE_THROW(Accumulator(capacity, 150), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()