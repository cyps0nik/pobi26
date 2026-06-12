#include <boost/test/unit_test.hpp>
#include "managers/CarManager.h"
#include "managers/ClientManager.h"
#include "managers/MechanicManager.h"
#include "managers/RepairManager.h"
#include "managers/ResourceManager.h"
#include "repositories/CarRepository.h"
#include "repositories/ClientRepository.h"
#include "repositories/MechanicRepository.h"
#include "repositories/RepairRepository.h"
#include "repositories/ResourceRepository.h"
#include "model/Car.h"
#include "model/Engine.h"
#include "model/Client.h"
#include "model/naprawa/Mechanic.h"
#include "model/naprawa/Repair.h"
#include "model/naprawa/Resource.h"
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;

BOOST_AUTO_TEST_SUITE(ManagersTestSuite)

BOOST_AUTO_TEST_CASE(CarManagerTest) {
    CarRepository repo;
    CarManager manager(repo);
    PoweredUniqPtr eng = std::make_unique<Engine>(1000, Petrol);
    ClientPtr cli = std::make_shared<Client>("A", "B", "123", "a@a", "PESEL");
    
    CarPtr car = manager.registerCar("Toyota", "Yaris", "VIN123", std::move(eng), cli);
    BOOST_REQUIRE(car != nullptr);
    BOOST_TEST(manager.getCar("VIN123") == car);
    manager.unregisterCar(car);
    BOOST_TEST(car->isArchive() == true);
}

BOOST_AUTO_TEST_CASE(ClientManagerTest) {
    ClientRepository repo;
    ClientManager manager(repo);
    ClientPtr client = manager.registerClient("Jan", "Kowalski", "123456789", "a@a", "12345");
    
    BOOST_REQUIRE(client != nullptr);
    BOOST_TEST(manager.getClient("12345") == client);
    manager.unregisterClient(client);
    BOOST_TEST(client->isArchive() == true);
}

BOOST_AUTO_TEST_CASE(MechanicManagerTest) {
    MechanicRepository repo;
    MechanicManager manager(repo);
    MechanicPtr mech = manager.registerMechanic("A", "B", Electrician);
    
    BOOST_REQUIRE(mech != nullptr);
    BOOST_TEST(manager.getMechanic(mech->getId()) == mech);
    manager.unregisterMechanic(mech);
    BOOST_TEST(mech->getBusy() == true);
}

BOOST_AUTO_TEST_CASE(RepairManagerTest) {
    RepairRepository repo;
    RepairManager manager(repo);
    CarPtr car = std::make_shared<Car>("Toyota", "Yaris", "VIN123", nullptr, nullptr);
    pt::ptime begin = pt::second_clock::local_time();
    
    RepairPtr repair = manager.registerRepair(begin, car);
    BOOST_REQUIRE(repair != nullptr);
    BOOST_TEST(manager.getRepair(repair->getId()) == repair);
    manager.unregisterRepair(repair);
    BOOST_TEST(repair->isArchive() == true);
}

BOOST_AUTO_TEST_CASE(ResourceManagerTest) {
    ResourceRepository repo;
    ResourceManager manager(repo);
    ResourcePtr res = manager.registerResource("Podnosnik", carLift);
    
    BOOST_REQUIRE(res != nullptr);
    BOOST_TEST(manager.getResource(res->getId()) == res);
    manager.unregisterResource(res);
    BOOST_TEST(res->getBusy() == true);
}

BOOST_AUTO_TEST_SUITE_END()