//
// Created by cypri on 1.06.2026.
//

#include "model/naprawa/Service.h"

#include <stdexcept>

Service::Service(const std::string &_name, const ResourceAbstractionPtr &_resource,
                 const MechanicAbstractionPtr &_mechanic) : name(_name), assignedResource(_resource),
                                                            assignedMechanic(_mechanic) {
    if (this->assignedMechanic == nullptr || this->assignedResource == nullptr) {
        throw std::invalid_argument("Usluga musi miec przypisanego mechanika i zasob!");
    }
}


const bool &Service::isRepaired() const {
    return this->repaired;
}

const std::string &Service::getName() const {
    return this->name;
}

std::string Service::getInfo() const {
    return "nazwa usługi: " + getName() + ", czy jest naprawione: " + (isRepaired() ? "tak" : "nie") + ", ";
}

const ResourceAbstractionPtr &Service::getAssignedResource() const {
    return this->assignedResource;
}
const MechanicAbstractionPtr &Service::getAssignedMechanic() const {
    return this->assignedMechanic;
}

