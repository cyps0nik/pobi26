#ifndef WARSZTATSAMOCHDOWY_PARTREGENARATION_H
#define WARSZTATSAMOCHDOWY_PARTREGENARATION_H
#include "TimeBasedService.h"

class PartRegenaration : public TimeBasedService {
private:
    int usage;

public:
    PartRegenaration(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin, const int &_usage);

    const int &getUsage() const;

    std::string getInfo() const override;

    double getServiceCost() const override;
};


#endif //WARSZTATSAMOCHDOWY_PARTREGENARATION_H
