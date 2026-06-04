//
// Created by cypri on 1.06.2026.
//

#include "../../../include/model/naprawa/Repair.h"
Repair::Repair(int _id, const pt::ptime &_beginTime) : id(_id), beginTime(_beginTime), repairCost(0), endTime(pt::not_a_date_time) {
if (_beginTime == pt::not_a_date_time) this->beginTime = pt::second_clock::local_time();
}
int Repair::getId() const {
    return this->id;
}
pt::ptime Repair::getBeginTime() const {
    return this->beginTime;
}
pt::ptime Repair::getEndTime() const {
    return this->endTime;
}
CarPtr Repair::getSamochod() const {
    return this->samochod;
}
int Repair::getServicesAmount() const {
    return services.size();
}
int Repair::getSingleServiceCost(ServicePtr service) const {
    if (service == nullptr) return 0;
    else return 1; //return service->getServiceCost();
}
int Repair::calculateTotal() const {
    int calosc = 0;
    for (int i = 0; i < services.size(); i++) {
        calosc += getSingleServiceCost(services[i]);
    }
    return calosc;
}








