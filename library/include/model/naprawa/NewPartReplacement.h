#ifndef WARSZTATSAMOCHODOWY_NEWPARTREPLACEMENT_H
#define WARSZTATSAMOCHODOWY_NEWPARTREPLACEMENT_H
#include "TimeBasedService.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class NewPartReplacement : public TimeBasedService {
private:
    unsigned int newPartPrice;

    // Dodajemy uprawnienia BOOSTOWI
    NewPartReplacement() = default;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // 1. Najpierw serializujemy klasę bazową
        ar & boost::serialization::base_object<TimeBasedService>(*this);

        // 2. Potem zmienne z tej konkretnej klasy
        ar & newPartPrice;
    }
public:
    NewPartReplacement(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin, const unsigned int &_partPrice, const ResourceAbstractionPtr& _resource, const MechanicAbstractionPtr& _mechanic);

    const unsigned int& getNewPartPrice() const;

    double getServiceCost() const override;

    std::string getInfo() const override;
};


#endif //WARSZTATSAMOCHODOWY_NEWPARTREPLACEMENT_H
