#include <boost/test/unit_test.hpp>
#include "model/naprawa/PartRegenaration.h"
#include "model/naprawa/Resource.h"
#include "model/naprawa/Mechanic.h"
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;

struct PartRegenarationFixture {
    std::string name = "Regeneracja";
    int hourPrice = 100;
    int usage = 30;
    pt::ptime begin = pt::ptime(boost::gregorian::date(2026, 1, 1), pt::hours(10));
    pt::ptime end = pt::ptime(boost::gregorian::date(2026, 1, 1), pt::hours(12));
    ResourceAbstractionPtr resource;
    MechanicAbstractionPtr mechanic;

    PartRegenarationFixture() {
        resource = std::make_shared<Resource>(1, "Podnosnik", carLift);
        mechanic = std::make_shared<Mechanic>(1, "Adam", "Nowak", engineMechanic);
    }
};

BOOST_FIXTURE_TEST_SUITE(PartRegenarationTest, PartRegenarationFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndCostTest) {
    PartRegenaration pr(name, hourPrice, begin, usage, resource, mechanic);
    pr.endService(end);
    BOOST_TEST(pr.getUsage() == usage);
    BOOST_TEST(pr.getHours() == 2);
    BOOST_TEST(pr.getServiceCost() == 300.0);
}

BOOST_AUTO_TEST_CASE(Exceptions) {
    BOOST_REQUIRE_THROW(PartRegenaration(name, hourPrice, begin, -10, resource, mechanic), std::invalid_argument);
    BOOST_REQUIRE_THROW(PartRegenaration(name, hourPrice, begin, 110, resource, mechanic), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()