#include <boost/test/unit_test.hpp>
#include "model/naprawa/Repair.h"
#include "model/Car.h"
#include "model/Engine.h"
#include "model/Client.h"
#include "model/naprawa/DiagnosticService.h"
#include "model/naprawa/Resource.h"
#include "model/naprawa/Mechanic.h"
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;

struct RepairFixture {
    int id = 1;
    pt::ptime begin = pt::ptime(boost::gregorian::date(2026, 1, 1), pt::hours(10));
    CarPtr car;
    ServicePtr service;

    RepairFixture() {
        PoweredUniqPtr engine = std::make_unique<Engine>(1000, Petrol);
        ClientPtr client = std::make_shared<Client>("Jan", "Kowalski", "123456789", "a@a.pl", "11111111111");
        car = std::make_shared<Car>("Toyota", "Yaris", "VIN123", std::move(engine), client);
        ResourceAbstractionPtr res = std::make_shared<Resource>(1, "Res", carLift);
        MechanicAbstractionPtr mech = std::make_shared<Mechanic>(1, "Mech", "Mech", Electrician);
        service = std::make_shared<DiagnosticService>("Diag", 100, res, mech);
    }
};

BOOST_FIXTURE_TEST_SUITE(RepairTest, RepairFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndServiceManagement) {
    Repair repair(id, begin, car);
    BOOST_TEST(repair.getId() == id);
    BOOST_TEST(repair.getBeginTime() == begin);
    BOOST_TEST(repair.getCar() == car);
    BOOST_TEST(repair.isArchive() == false);
    
    repair.add(service);
    BOOST_TEST(repair.getServicesAmount() == 1);
    BOOST_TEST(repair.getSingleServiceCost(service) == 100.0);
    BOOST_TEST(repair.calculateTotal() == 100.0);

    repair.remove(service);
    BOOST_TEST(repair.getServicesAmount() == 0);
}

BOOST_AUTO_TEST_SUITE_END()