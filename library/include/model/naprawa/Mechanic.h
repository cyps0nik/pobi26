#ifndef WARSZTATSAMOCHODOWY_MECHANIC_H
#define WARSZTATSAMOCHODOWY_MECHANIC_H
#include "MechanicAbstraction.h"
#include <string>

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp> // Konieczne przy dziedziczeniu

enum Specialization {
    Electrician = 10, engineMechanic = 20, Diagnostician = 30, VAGSpecialist = 40, Master = 50
};

class Mechanic : public MechanicAbstraction {
private:
    int id;
    std::string firstName;
    std::string lastName;
    Specialization specialize;
    bool isBusy;

    // Dodajemy uprawnienia BOOSTOWI
    Mechanic() = default;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        // Najpierw serializujemy klasę bazową
        ar & boost::serialization::base_object<MechanicAbstraction>(*this);
        ar & id;
        ar & firstName;
        ar & lastName;
        ar & specialize;
        ar & isBusy;
    }
public:
    Mechanic(const int &di, const std::string &_first, const std::string &_last, const Specialization &_spec);

    const int &getId() const;

    const std::string &getFirstName() const;

    const std::string &getLastName() const;

    const bool &getBusy() const;

    void setBusy(const bool &zmiana);


    const Specialization &getSpecialization() const;

    bool isAvailable() const;

    std::string getInfo() const;
};


#endif //WARSZTATSAMOCHODOWY_MECHANIC_H
