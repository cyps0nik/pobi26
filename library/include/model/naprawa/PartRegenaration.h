#ifndef WARSZTATSAMOCHDOWY_PARTREGENARATION_H
#define WARSZTATSAMOCHDOWY_PARTREGENARATION_H
#include "TimeBasedService.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class PartRegenaration : public TimeBasedService {
private:
    int usage;

    // Dodajemy uprawnienia BOOSTOWI
    PartRegenaration() = default;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // 1. Najpierw serializujemy klasę bazową
        ar & boost::serialization::base_object<TimeBasedService>(*this);

        // 2. Potem zmienne z tej konkretnej klasy
        ar & usage;
    }
public:
    PartRegenaration(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin, const int &_usage, const ResourceAbstractionPtr& _resource, const MechanicAbstractionPtr& _mechanic);

    const int &getUsage() const;

    std::string getInfo() const override;

    double getServiceCost() const override;
};


#endif //WARSZTATSAMOCHDOWY_PARTREGENARATION_H
