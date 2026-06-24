#include <boost/test/unit_test.hpp>
#include "model/naprawa/DiagnosticService.h"
#include "model/naprawa/Resource.h"
#include "model/naprawa/Mechanic.h"
#include <stdexcept>

struct DiagnosticServiceFixture {
    std::string name = "Diag";
    int price = 100;
    ResourceAbstractionPtr resource;
    MechanicAbstractionPtr mechanic;

    DiagnosticServiceFixture() {
        resource = std::make_shared<Resource>(1, "Komputer", diagnosticComputer);
        mechanic = std::make_shared<Mechanic>(1, "Jan", "Kowalski", Diagnostician);
    }
};

BOOST_FIXTURE_TEST_SUITE(DiagnosticServiceTest, DiagnosticServiceFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGetters) {
    DiagnosticService ds(name, price, resource, mechanic);
    BOOST_TEST(ds.getName() == name);
    BOOST_TEST(ds.getServiceCost() == price);
    BOOST_TEST(ds.getAssignedResource() == resource);
    BOOST_TEST(ds.getAssignedMechanic() == mechanic);
    BOOST_TEST(ds.isRepaired() == true);
}

BOOST_AUTO_TEST_CASE(Exceptions) {
    BOOST_REQUIRE_THROW(DiagnosticService(name, -50, resource, mechanic), std::invalid_argument);
    BOOST_REQUIRE_THROW(DiagnosticService(name, price, nullptr, mechanic), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()