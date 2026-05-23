#ifndef PROJEKT_CLIENT_H
#define PROJEKT_CLIENT_H
#include <string>
#include <vector>
#include "typedefs.h"

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string email;
    std::string personalID;
    std::vector<CarPtr> cars;

public:
    Client(std::string& _firstName, std::string& _lastName, std::string& _phoneNumber, std::string& _email,
           std::string& _personalID);

    const std::string &getFirstName();

    const std::string &getLastName();

    const std::string &getPhoneNumber();

    const std::string &getEmail();

    const std::string &getPersonalID();
};


#endif
