//
// Created by cypri on 1.06.2026.
//

#include "model/naprawa/Repair.h"

#include "model/Car.h"
#include "model/PoweredBy.h"

Repair::Repair(const int &_id, const pt::ptime &_beginTime, const CarPtr &_car) : id(_id), beginTime(_beginTime),
    repairedCar(_car), repairCost(0), services() {
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
        if (service == nullptr) return 0.0;
        else
        {
            if (service == services[i]) {
                return services[i]->getServiceCost() * repairedCar->getPowerSource()->getMultiplier();
            }
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

double Repair::calculateTotal() {
    double suma = 0;
    for (int i = 0; i < services.size(); i++) {
        if (services[i] != nullptr)
        {
            suma += getSingleServiceCost(services[i]);
        }
        else
        {
            suma += 0;
        }
    }
    this->repairCost = suma;
    return suma;
}

void Repair::add(const ServicePtr &service) {
    if (service != nullptr) {
        auto it = std::find(services.begin(), services.end(), service);
        if (it == services.end()) {
            services.push_back(service);
        }
    }
}

void Repair::remove(const ServicePtr &service) {
    if (service != nullptr) {
        auto it = std::find(services.begin(), services.end(), service);
        if (it != services.end()) {
            services.erase(it);
        }
    }
}

ServicePtr Repair::get(const ServicePtr &service) {
    for (int i = 0; i < services.size(); i++) {
        if (service == services[i] && services[i] != nullptr && service != nullptr) {
            return services[i];
        }
        else return nullptr;
    }
    return nullptr;
}

std::string Repair::getInfo() const {
    std::string tym = "";
    std::stringstream ss;
    ss << "Poczatek repair: " << getBeginTime() << ", koniec repair: " << getEndTime();
    for (int i = 0; i < services.size(); i++) {
       if (services[i] != nullptr) {
            tym += services[i]->getInfo();
        }
        else
        {
            tym += "";
        }
    }
    return "Identyfikator: " + std::to_string(getId()) + ", Cena za calosc z mnoznikiem: " +
           std::to_string(getRepairCost()) + ", " + ss.str();
}

const double &Repair::getRepairCost() const {
    return this->repairCost;
}
std::string Repair::getSingleServiceInfo(const ServicePtr &service) const {
    for (int i = 0; i < services.size(); i++) {
        if (service == services[i]) {
            return services[i]->getInfo();
        }
    }
    return "";
}
std::string Repair::getRepairedCarInfo() const {
    return getCar()->getInfo();
}

void Repair::endRepair() {
    if (endTime.is_not_a_date_time())
    {
        for (int i = 0; i < services.size(); i++)
        {
            if (services[i] == nullptr) continue;
            if (services[i]->isRepaired() == false) return;
        }
        endTime = pt::second_clock::local_time();
    }
}