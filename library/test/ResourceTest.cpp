#include <boost/test/unit_test.hpp>
#include "model/naprawa/Resource.h"

struct ResourceFixture {
    int id = 1;
    std::string name = "Podnosnik kolumnowy";
    ResourceType type = carLift;
};

BOOST_FIXTURE_TEST_SUITE(ResourceTest, ResourceFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGetters) {
    Resource res(id, name, type);
    BOOST_TEST(res.getId() == id);
    BOOST_TEST(res.getResourceName() == name);
    BOOST_TEST(res.getResourceType() == type);
    BOOST_TEST(res.isAvailable() == true);
    BOOST_TEST(res.getBusy() == false);
}

BOOST_AUTO_TEST_CASE(StateChange) {
    Resource res(id, name, type);
    res.setBusy(true);
    BOOST_TEST(res.getBusy() == true);
    BOOST_TEST(res.isAvailable() == false);
}

BOOST_AUTO_TEST_SUITE_END()