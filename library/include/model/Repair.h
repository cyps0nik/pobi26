//
// Created by cypri on 1.06.2026.
//

#ifndef WARSZTATSAMOCHDOWY_REPAIR_H
#define WARSZTATSAMOCHDOWY_REPAIR_H
#include <boost/date_time.hpp>
#include <vector>
#include "typedefs.h"
#include "model/Service.h"
#include "model/Repair.h"
namespace pt = boost::posix_time;
class Repair : std::enable_shared_from_this<Repair>{
    int id;
    int repairCost;
    pt::ptime beginTime;
    pt::ptime endTime;
    std::vector<ServicePtr> services;
    CarPtr samochod;
public:
    Repair(int _id,  const pt::ptime &_beginTime);
    int getId() const;
    pt::ptime getBeginTime() const;
    pt::ptime getEndTime() const;
    CarPtr getSamochod() const;
    int getServicesAmount() const;
    int getSingleServiceCost(ServicePtr service) const;
    int calculateTotal() const;

};


#endif //WARSZTATSAMOCHDOWY_REPAIR_H