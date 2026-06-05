//
// Created by cypri on 1.06.2026.
//

#ifndef WARSZTATSAMOCHDOWY_REPAIR_H
#define WARSZTATSAMOCHDOWY_REPAIR_H
#include <boost/date_time.hpp>
#include <vector>
#include "typedefs.h"
#include "Service.h"
#include "model/naprawa/Repair.h"
namespace pt = boost::posix_time;
class Repair : std::enable_shared_from_this<Repair>{
    int id;
    int repairCost;
    pt::ptime beginTime;
    pt::ptime endTime;
    std::vector<ServicePtr> services;
    CarPtr car;
public:
    Repair(const int& _id,  const pt::ptime &_beginTime,const CarPtr& _car);
    const int& getId() const;
    const pt::ptime& getBeginTime() const;
    const pt::ptime& getEndTime() const;
    CarPtr getCar() const;
    int getServicesAmount() const;
    int getSingleServiceCost(ServicePtr service) const;
    int calculateTotal() const;

    //void add(const ServicePtr& service);

    //void remove(const ServicePtr& service);

    //ServicePtr get(int index);

};


#endif //WARSZTATSAMOCHDOWY_REPAIR_H