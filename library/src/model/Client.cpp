#include "model/Client.h"
#include <algorithm>
#include <string>
#include <stdexcept>

Client::Client(const std::string &_firstName, const std::string &_lastName, const std::string &_phoneNumber,
               const std::string &_email, const std::string &_personalID) {
    this->firstName = _firstName;
    this->lastName = _lastName;
    if (_phoneNumber.size() > 15) throw std::invalid_argument("PhoneNumber size exceeded");
    else this->phoneNumber = _phoneNumber;
    if (_email.find('@') == std::string::npos) throw std::invalid_argument("Invalid email");
    else this->email = _email;
    this->personalID = _personalID;
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

// void Client::add(const CarPtr &car) {
//     if (car == nullptr) return;
//     else cars.push_back(car);
// }
//
// CarPtr Client::get(int index) {
//     if (index < 0 || index >= cars.size()) return nullptr;
//     else return cars[index];
// }
//
// void Client::remove(const CarPtr& car) {
// if (car== nullptr) return;
//     else {
//         cars.erase(std::remove(cars.begin(), cars.end(), car), cars.end());
//     }
// }

std::string Client::getInfo() const {
    std::string info = "Imie: " + getFirstName() + ", Nazwisko: " + getLastName() + ", PESEL: " + getPersonalID();
    info += ", Numer telefonu: " + getPhoneNumber() + ", Email: " + getEmail();
    return info;
}

