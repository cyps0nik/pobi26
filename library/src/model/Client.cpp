#include "model/Client.h"
Client::Client(std::string& _firstName, std::string& _lastName, std::string& _phoneNumber, std::string& _email, std::string &_personalID) : cars(){
    this->firstName = _firstName;
    this->lastName = _lastName;
    this->phoneNumber = _phoneNumber;
    this->email = _email;
    this->personalID = _personalID;
}
const std::string &Client::getFirstName() {
    return this->firstName;
}
const std::string &Client::getLastName() {
    return this->lastName;
}
const std::string &Client::getPhoneNumber() {
    return this->phoneNumber;
}
const std::string &Client::getEmail() {
    return this->email;
}

