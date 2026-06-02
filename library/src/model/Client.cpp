#include "model/Client.h"
Client::Client(std::string _firstName, std::string _lastName, std::string _phoneNumber, std::string _email, std::string _personalID) {
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
const std::string &Client::getPersonalID() {
    return this->personalID;
}
void Client::setEmail(const std::string &email) {
    if (email == "") return;
    else this->email = email;
}
void Client::setPhoneNumber(const std::string &phoneNumber) {
    if (phoneNumber == "") return;
    else this->phoneNumber = phoneNumber;
}


