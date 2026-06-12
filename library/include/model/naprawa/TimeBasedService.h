#ifndef WARSZTATSAMOCHDOWY_TIMEBASEDSERVICE_H
#define WARSZTATSAMOCHDOWY_TIMEBASEDSERVICE_H
#include "Service.h"
#include <boost/date_time.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

namespace pt = boost::posix_time;

class TimeBasedService : public Service {
private:
    int partHourlyPrice;
    pt::ptime beginTime;
    pt::ptime endTime;

    // Dodajemy uprawnienia BOOSTOWI
    TimeBasedService() = default;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // 1. Najpierw serializujemy klasę bazową
        ar & boost::serialization::base_object<Service>(*this);

        // 2. Potem zmienne z tej konkretnej klasy
        ar & partHourlyPrice;
        ar & beginTime;
        ar & endTime;
    }

public:
    TimeBasedService(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin, const ResourceAbstractionPtr& _resource, const MechanicAbstractionPtr& _mechanic);

    virtual ~TimeBasedService() = 0;

    const int &getPartHourlyPrice() const;

    const pt::ptime &getBeginTime() const;

    const pt::ptime &getEndTime() const;

    void endService(const pt::ptime &_endTime);

    double getServiceCost() const override;

    int getHours() const;

    std::string getInfo() const override;
};


#endif //WARSZTATSAMOCHDOWY_TIMEBASEDSERVICE_H
