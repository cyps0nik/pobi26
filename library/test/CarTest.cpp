#include <boost/test/unit_test.hpp>
#include "model/Car.h"
#include "typedefs.h"
#include "model/Client.h"
#include "model/Engine.h"

struct TestSuiteCarFixture {
    std::string testCarBrand = "BMW";
    std::string testCarModel = "Series 3";
    std::string testVIN = "1GKCS18R3J8511516";
    PoweredUniqPtr testEngine;
    ClientPtr testOwner;

    TestSuiteCarFixture() {
        testEngine = std::make_unique<Engine>(3000, Petrol);
        testOwner = std::make_shared<Client>("Mark", "Hazel", "607942512", "hazelowski@yahoo.com", "246930920");
    }
};

BOOST_FIXTURE_TEST_SUITE(CarTest, TestSuiteCarFixture)
    BOOST_AUTO_TEST_CASE(ConstructorTest) {
    Car samochod(testCarBrand, testCarModel, testVIN, std::move(testEngine), testOwner);
    }

BOOST_AUTO_TEST_SUITE_END()
