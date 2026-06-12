#include <boost/test/unit_test.hpp>
#include "repositories/CarRepository.h"
#include "repositories/ClientRepository.h"
#include "repositories/MechanicRepository.h"
#include "repositories/RepairRepository.h"
#include "repositories/ResourceRepository.h"
#include "model/Car.h"
#include "model/Client.h"
#include "model/Engine.h"
#include "model/naprawa/Mechanic.h"
#include "model/naprawa/Repair.h"
#include "model/naprawa/Resource.h"
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;

BOOST_AUTO_TEST_SUITE(RepositoriesTestSuite)

BOOST_AUTO_TEST_CASE(CarRepositoryTest) {
    CarRepository repo;
    ClientPtr client = std::make_shared<Client>("A", "B", "123", "a@a", "111");
    PoweredUniqPtr e1 = std::make_unique<Engine>(1000, Petrol);
    CarPtr car1 = std::make_shared<Car>("Toyota", "Yaris", "VIN1", std::move(e1), client);
    
    repo.add(car1);
    BOOST_TEST(repo.size() == 1);
    BOOST_TEST(repo.findByVin("VIN1") == car1);
    repo.remove(car1);
    BOOST_TEST(repo.size() == 0);
}

BOOST_AUTO_TEST_CASE(ClientRepositoryTest) {
    ClientRepository repo;
    ClientPtr client1 = std::make_shared<Client>("A", "B", "111", "a@a.com", "12345");
    
    repo.add(client1);
    BOOST_TEST(repo.size() == 1);
    BOOST_TEST(repo.findByPersonalId("12345") == client1);
    repo.remove(client1);
    BOOST_TEST(repo.size() == 0);
}

BOOST_AUTO_TEST_CASE(MechanicRepositoryTest) {
    MechanicRepository repo;
    MechanicPtr mech1 = std::make_shared<Mechanic>(1, "A", "B", Electrician);
    
    repo.add(mech1);
    BOOST_TEST(repo.size() == 1);
    BOOST_TEST(repo.findById(1) == mech1);
    repo.remove(mech1);
    BOOST_TEST(repo.size() == 0);
}

BOOST_AUTO_TEST_CASE(RepairRepositoryTest) {
    RepairRepository repo;
    CarPtr car1 = std::make_shared<Car>("Toyota", "Y", "V1", nullptr, nullptr);
    RepairPtr rep1 = std::make_shared<Repair>(1, pt::second_clock::local_time(), car1);
    
    repo.add(rep1);
    BOOST_TEST(repo.size() == 1);
    BOOST_TEST(repo.findById(1) == rep1);
    repo.remove(rep1);
    BOOST_TEST(repo.size() == 0);
}

BOOST_AUTO_TEST_CASE(ResourceRepositoryTest) {
    ResourceRepository repo;
    ResourcePtr res1 = std::make_shared<Resource>(1, "Lift", carLift);
    
    repo.add(res1);
    BOOST_TEST(repo.size() == 1);
    BOOST_TEST(repo.findById(1) == res1);
    repo.remove(res1);
    BOOST_TEST(repo.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()