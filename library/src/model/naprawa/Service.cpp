//
// Created by cypri on 1.06.2026.
//

#include "model/naprawa/Service.h"

Service::Service(const std::string &_name) : name(_name), repaired(false) {
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
