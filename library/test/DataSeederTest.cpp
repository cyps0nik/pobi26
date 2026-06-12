#include <boost/test/unit_test.hpp>
#include "DataSeeder.h"
#include "StorageContainer.h"
#include <cstdio>

BOOST_AUTO_TEST_SUITE(DataSeederTest)

BOOST_AUTO_TEST_CASE(SeedingTest) {
    StorageContainer storage;
    std::string filename = "test_seeder_data.txt";
    DataSeeder::prepareSystem(storage, filename);
    
    BOOST_TEST(storage.getClientRepository().size() > 0);
    BOOST_TEST(storage.getCarRepository().size() > 0);
    BOOST_TEST(storage.getMechanicRepository().size() > 0);
    BOOST_TEST(storage.getResourceRepository().size() > 0);
    BOOST_TEST(storage.getRepairRepository().size() > 0);
    
    std::remove(filename.c_str());
}

BOOST_AUTO_TEST_SUITE_END()