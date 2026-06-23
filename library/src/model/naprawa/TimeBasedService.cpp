#include "model/naprawa/TimeBasedService.h"

#include "model/naprawa/MechanicAbstraction.h"
#include "model/naprawa/ResourceAbstraction.h"

TimeBasedService::TimeBasedService(const std::string &_name, const int &_hourPrice,
                                   const pt::ptime &_begin, const ResourceAbstractionPtr& _resource, const MechanicAbstractionPtr& _mechanic) : Service(_name, _resource, _mechanic), partHourlyPrice(_hourPrice),
                                                                                                                                                beginTime(_begin) {
    if (_begin == pt::not_a_date_time) {
        this->beginTime = pt::second_clock::local_time();
    }
}

TimeBasedService::~TimeBasedService() {
}

const int &TimeBasedService::getPartHourlyPrice() const {
    return this->partHourlyPrice;
}

const pt::ptime &TimeBasedService::getBeginTime() const {
    return this->beginTime;
}

const pt::ptime &TimeBasedService::getEndTime() const {
    return this->endTime;
}

void TimeBasedService::endService(const pt::ptime &_endTime) {
    if (getEndTime() != pt::not_a_date_time) {
        return;
    } else if (_endTime == pt::not_a_date_time) {
        this->endTime = pt::second_clock::local_time();
    } else if ((_endTime < getBeginTime()) != 0) {
        this->endTime = this->beginTime;
    } else {
        this->endTime = _endTime;
    }
    MechanicAbstractionPtr _mechanic = getAssignedMechanic();
    _mechanic->setBusy(false);
    ResourceAbstractionPtr _resource = getAssignedResource();
    _resource->setBusy(false);
}

std::string TimeBasedService::getInfo() const {
    std::stringstream ss1, ss2;
    ss1 << getBeginTime();
    ss2 << getEndTime();
    return "Serwis czasowy, " + Service::getInfo() + ", cena za godzine pracy: " + std::to_string(getPartHourlyPrice())
           + ", poczatek serwisu: " + ss1.str() + ", koniec serwisu: " + ss2.str();
}

double TimeBasedService::getServiceCost() const {
    return getHours() * getPartHourlyPrice();
}

int TimeBasedService::getHours() const {
        if (getEndTime() == pt::not_a_date_time) {
            return 0;
        }
        pt::time_period rent_time(getBeginTime(), getEndTime());
        if (rent_time.length().minutes() == 0 && rent_time.length().hours() == 0) return 0;
        return std::ceil(rent_time.length().total_nanoseconds() / 3600000000000.0);
}

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT(TimeBasedService)
