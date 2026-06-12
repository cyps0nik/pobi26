#include <boost/test/unit_test.hpp>
#include "model/naprawa/Mechanic.h"

struct MechanicFixture {
    int id = 1;
    std::string fName = "Marek";
    std::string lName = "Klucz";
    Specialization spec = Electrician;
};

BOOST_FIXTURE_TEST_SUITE(MechanicTest, MechanicFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGetters) {
    Mechanic mech(id, fName, lName, spec);
    BOOST_TEST(mech.getId() == id);
    BOOST_TEST(mech.getFirstName() == fName);
    BOOST_TEST(mech.getLastName() == lName);
    BOOST_TEST(mech.getSpecialization() == spec);
    BOOST_TEST(mech.isAvailable() == true);
    BOOST_TEST(mech.getBusy() == false);
}

BOOST_AUTO_TEST_CASE(StateChange) {
    Mechanic mech(id, fName, lName, spec);
    mech.setBusy(true);
    BOOST_TEST(mech.getBusy() == true);
    BOOST_TEST(mech.isAvailable() == false);
}

BOOST_AUTO_TEST_SUITE_END()