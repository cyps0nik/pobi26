#ifndef WARSZTATSAMOCHDOWY_ENGINE_H
#define WARSZTATSAMOCHDOWY_ENGINE_H
#include "PoweredBy.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

enum FuelType {
    Petrol = 10,
    Diesel = 12
};
class Engine : public PoweredBy {
private:
    int engineDisplacement;
    FuelType typPaliwa;

    // Dodajemt uprawnienia BOOSTOWI
    Engine() = default;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // 1. Najpierw serializujemy klasę bazową
        ar & boost::serialization::base_object<PoweredBy>(*this);

        // 2. Potem zmienne z tej konkretnej klasy
        ar & engineDisplacement;
        ar & typPaliwa;
    }
public:
    Engine(const int& _engineDisplacement, const FuelType& _typPaliwa);
    const int& getEngineDisplacement() const;
    const FuelType& getFuelType() const;
    double getMultiplier() const override;
};


#endif //WARSZTATSAMOCHDOWY_ENGINE_H
