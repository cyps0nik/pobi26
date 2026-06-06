//
// Created by cypri on 1.06.2026.
//

#include "model/naprawa/Repair.h"

#include "model/Car.h"
#include "model/PoweredBy.h"

Repair::Repair(const int &_id, const pt::ptime &_beginTime, const CarPtr &_car) : id(_id), beginTime(_beginTime),
    repairedCar(_car),repairCost(0), services() {
    if (_beginTime == pt::not_a_date_time) this->beginTime = pt::second_clock::local_time();
}

const int &Repair::getId() const {
    return this->id;
}

CarPtr Repair::getCar() const {
    return this->repairedCar;
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
            return services[i]->getServiceCost() * repairedCar->getPowerSource()->getMultiplier();
        }
    }
    return 0.0;
}

bool Repair::isArchive() const {
    return archive;
}

void Repair::setArchive(bool arch) {
    archive = arch;
}

double Repair::calculateTotal() const {
    double suma = 0;
    for (int i = 0; i < services.size(); i++) {
        suma += getSingleServiceCost(services[i]);
    }
    return suma;
}

void Repair::add(const ServicePtr &service) {
    if (service == nullptr) return;
    else services.push_back(service);
}

void Repair::remove(const ServicePtr &service) {
    if (service != nullptr) {
        services.erase(std::remove(services.begin(), services.end(), service), services.end());
    }
}

ServicePtr Repair::get(const ServicePtr &service) {
    for (int i = 0; i < services.size(); i++) {
        if (service == services[i]) {
            return services[i];
        }
    }
    return nullptr;
}
