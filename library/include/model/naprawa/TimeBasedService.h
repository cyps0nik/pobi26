#ifndef WARSZTATSAMOCHDOWY_TIMEBASEDSERVICE_H
#define WARSZTATSAMOCHDOWY_TIMEBASEDSERVICE_H
#include "Service.h"
#include <boost/date_time.hpp>
namespace pt = boost::posix_time;

class TimeBasedService : public Service {
private:
    int partHourlyPrice;
    pt::ptime beginTime;
    pt::ptime endTime;

public:
    TimeBasedService(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin);

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
