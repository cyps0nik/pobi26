#ifndef WARSZTATSAMOCHDOWY_ACCUMULATOR_H
#define WARSZTATSAMOCHDOWY_ACCUMULATOR_H
#include "PoweredBy.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class Accumulator : public PoweredBy {
private:
    int capacityKWh;
    int degradationLevel;

    // Dodajemy uprawnienia BOOSTOWI
    Accumulator() = default;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // 1. Najpierw serializujemy klasę bazową
        ar & boost::serialization::base_object<PoweredBy>(*this);

        // 2. Potem zmienne z tej konkretnej klasy
        ar & capacityKWh;
        ar & degradationLevel;
    }
public:
    Accumulator(const int& _capacityKWh, const int& _degradationLevel);
    const int& getCapacityKWh() const;
    const int& getDegradationLevel() const;
    double getMultiplier() const override;
    std::string getInfo() const override;
};


#endif //WARSZTATSAMOCHDOWY_ACCUMULATOR_H
