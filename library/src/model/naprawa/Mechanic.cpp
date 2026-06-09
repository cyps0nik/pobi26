#include "model/naprawa/Mechanic.h"

Mechanic::Mechanic(const int &di, const std::string &_first, const std::string &_last,
                   const Specialization &_spec) : id(di), firstName(_first), lastName(_last), specialize(_spec),
                                                  isBusy(false) {
}

const int &Mechanic::getId() const {
    return this->id;
}

const std::string &Mechanic::getFirstName() const {
    return this->firstName;
}

const std::string &Mechanic::getLastName() const {
    return this->lastName;
}

const Specialization &Mechanic::getSpecialization() const {
    return this->specialize;
}

bool Mechanic::isAvailable() const {
    if (this->isBusy) return false;
    else return true;
}

std::string Mechanic::getInfo() const {
    std::string result, _bool;
    switch (getSpecialization()) {
        case Specialization::Electrician: result = "Elektryk";
            break;
        case Specialization::engineMechanic: result = "silnikowy";
            break;
        case Specialization::Diagnostician: result = "Diagnosta";
            break;
        case Specialization::VAGSpecialist: result = "Auta koncernu VAG";
            break;
        default: result = "Wszechwiedzacy";
            break;
    }
    if (isAvailable()) _bool = "dostepny";
    else _bool = "niedostepny";
    return "Mechanik, specjalizacja: " + result + ", imie: " + getFirstName() + ", nazwisko: " + getLastName() + ", dostepnosc: " +
           _bool;
}
