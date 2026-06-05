//
// Created by cypri on 1.06.2026.
//

#include "model/naprawa/Repair.h"

#include "model/Car.h"
#include "model/PoweredBy.h"

Repair::Repair(const int &_id, const pt::ptime &_beginTime, const CarPtr &_car) : id(_id), beginTime(_beginTime),
                                                                                  car(_car), services() {
    this->repairCost = 0;
    if (_beginTime == pt::not_a_date_time) this->beginTime = pt::second_clock::local_time();
}
const int &Repair::getId() const {
    return this->id;
}
CarPtr Repair::getCar() const {
    return this->car;
}
const pt::ptime &Repair::getBeginTime() const {
    return this->beginTime;
}
const pt::ptime &Repair::getEndTime() const {
    return this->endTime;
}
int Repair::getServicesAmount() const {
    return services.size();
}

double Repair::getSingleServiceCost(const ServicePtr &service) const {
    for (int i = 0; i < services.size(); i++) {
        if (service == services[i]) {
            return services[i]->getServiceCost() * car->getPowerSource()->getMultiplier();
        }
    }
    return 0.0;
}



