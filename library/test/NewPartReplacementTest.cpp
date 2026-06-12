#include <boost/test/unit_test.hpp>
#include "model/naprawa/NewPartReplacement.h"
#include "model/naprawa/Resource.h"
#include "model/naprawa/Mechanic.h"
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;

struct NewPartReplacementFixture {
    std::string name = "Wymiana";
    int hourPrice = 100;
    unsigned int partPrice = 500;
    pt::ptime begin = pt::ptime(boost::gregorian::date(2026, 1, 1), pt::hours(10));
    pt::ptime end = pt::ptime(boost::gregorian::date(2026, 1, 1), pt::hours(12));
    ResourceAbstractionPtr resource;
    MechanicAbstractionPtr mechanic;

    NewPartReplacementFixture() {
        resource = std::make_shared<Resource>(1, "Podnosnik", carLift);
        mechanic = std::make_shared<Mechanic>(1, "Adam", "Nowak", engineMechanic);
    }
};

BOOST_FIXTURE_TEST_SUITE(NewPartReplacementTest, NewPartReplacementFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndCostTest) {
    NewPartReplacement npr(name, hourPrice, begin, partPrice, resource, mechanic);
    npr.endService(end);
    BOOST_TEST(npr.getNewPartPrice() == partPrice);
    BOOST_TEST(npr.getHours() == 2);
    BOOST_TEST(npr.getServiceCost() == 700.0);
}

BOOST_AUTO_TEST_SUITE_END()