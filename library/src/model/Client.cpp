#include "model/Client.h"
#include <algorithm>
#include <stdexcept>

Client::Client(const std::string &_firstName, const std::string &_lastName, const std::string &_phoneNumber,
               const std::string &_email, const std::string &_personalID) : firstName(_firstName), lastName(_lastName),
                                                                            personalID(_personalID) {
    if (_phoneNumber.size() > 15) throw std::invalid_argument("PhoneNumber size exceeded");
    else this->phoneNumber = _phoneNumber;
    if (_email.find('@') == std::string::npos) throw std::invalid_argument("Invalid email");
    else this->email = _email;
}

const std::string &Client::getFirstName() const {
    return this->firstName;
}

const std::string &Client::getLastName() const {
    return this->lastName;
}

const std::string &Client::getPhoneNumber() const {
    return this->phoneNumber;
}

const std::string &Client::getEmail() const {
    return this->email;
}

const std::string &Client::getPersonalID() const {
    return this->personalID;
}

void Client::setEmail(const std::string &email) {
    if (email.empty() || email.find('@') == std::string::npos) return;
    else this->email = email;
}

void Client::setPhoneNumber(const std::string &phoneNumber) {
    if (phoneNumber.empty()) return;
    else this->phoneNumber = phoneNumber;
}

std::string Client::getInfo() const {
    std::string info = "Imie: " + getFirstName() + ", Nazwisko: " + getLastName() + ", PESEL: " + getPersonalID();
    info += ", Numer telefonu: " + getPhoneNumber() + ", Email: " + getEmail();
    return info;
}

bool Client::isArchive() const {
    return archive;
}

void Client::setArchive(bool arch) {
    archive = arch;
}
