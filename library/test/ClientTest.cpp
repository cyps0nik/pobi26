#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "typedefs.h"
struct TestSuiteClientFixture {
     std::string testFirstName = "Jon";
     std::string testLastName = "Arbuckle";
     std::string testPhoneNumber = "600700900";
     std::string testEmail = "jonarbuck@gmail.com";
     std::string testPersonalID = "0123456789";

    TestSuiteClientFixture() = default;

    ~TestSuiteClientFixture() = default;
};
BOOST_FIXTURE_TEST_SUITE(TestClient, TestSuiteClientFixture)
BOOST_AUTO_TEST_CASE(ConstructorTest) {
    Client klient(testFirstName, testLastName, testPhoneNumber, testEmail, testPersonalID);
    BOOST_TEST(klient.getFirstName() == testFirstName);
    BOOST_TEST(klient.getLastName() == testLastName);
    BOOST_TEST(klient.getPhoneNumber() == testPhoneNumber);
    BOOST_TEST(klient.getEmail() == testEmail);
    BOOST_TEST(klient.getPersonalID() == testPersonalID);

}
BOOST_AUTO_TEST_CASE(SetterTest) {
    Client klient2(testFirstName, testLastName, testPhoneNumber, testEmail, testPersonalID);

}
BOOST_AUTO_TEST_SUITE_END()
