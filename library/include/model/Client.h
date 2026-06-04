#ifndef PROJEKT_CLIENT_H
#define PROJEKT_CLIENT_H
#include <string>
#include <vector>
#include "typedefs.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp> // Potrzebne żeby Boost umiał zapisać stringa

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string email;
    std::string personalID;
    std::vector<CarPtr> cars;

    // Dajemy uprawnienia Boostowi
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & firstName;  // Zapisujemy/odczytujemy imię
        ar & lastName;   // Zapisujemy/odczytujemy nazwisko
        ar & phoneNumber;   // Zapisujemy/odczytujemy numer telefonu
        ar & email;   // Zapisujemy/odczytujemy email
        ar & personalID; // Zapisujemy/odczytujemy Pesel
        ar & cars; // Zapisujemy/odczytujemy samochody
    }
public:
    Client(const std::string &_firstName, const std::string &_lastName, const std::string &_phoneNumber,
           const std::string &_email,
           const std::string &_personalID);

    ~Client() = default;

    const std::string &getFirstName() const;

    const std::string &getLastName() const;

    const std::string &getPhoneNumber() const;

    const std::string &getEmail() const;

    const std::string &getPersonalID() const;

    void setPhoneNumber(const std::string &phoneNumber);

    void setEmail(const std::string &email);

    void add(const CarPtr& car);

    void remove(const CarPtr& car);

    CarPtr get(int index);
};


#endif
