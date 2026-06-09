#ifndef WARSZTATSAMOCHODOWY_NEWPARTREPLACEMENT_H
#define WARSZTATSAMOCHODOWY_NEWPARTREPLACEMENT_H
#include "TimeBasedService.h"

class NewPartReplacement : public TimeBasedService {
private:
    unsigned int newPartPrice;

public:
    NewPartReplacement(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin, const unsigned int &_partPrice, const ResourceAbstractionPtr& _resource, const MechanicAbstractionPtr& _mechanic);

    const unsigned int& getNewPartPrice() const;

    double getServiceCost() const override;

    std::string getInfo() const override;
};


#endif //WARSZTATSAMOCHODOWY_NEWPARTREPLACEMENT_H
