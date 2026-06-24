#include "model/Car.h"
#include "model/PoweredBy.h"
#include <utility>

#include "model/Client.h"

Car::Car(const std::string &_carBrand, const std::string &_carModel, const std::string &_VIN, PoweredUniqPtr _power
         , const ClientPtr &_owner) : carBrand(_carBrand), carModel(_carModel), VIN(_VIN),
                                      powerSource(std::move(_power)), owner(_owner) {
}

const std::string &Car::getCarBrand() const {
    return this->carBrand;
}

const std::string &Car::getCarModel() const {
    return this->carModel;
}

const std::string &Car::getVIN() const {
    return this->VIN;
}

PoweredBy *Car::getPowerSource() const {
    return this->powerSource.get();
}

const ClientPtr &Car::getOwner() const {
    return this->owner;
}


std::string Car::getInfo() const {
    std::string clientInfo = "Brak (nullptr)";
    if (getOwner() != nullptr) {
        clientInfo = getOwner()->getFirstName() + " " + getOwner()->getLastName();
    }

    std::string powerInfo = "Brak (nullptr)";
    if (this->powerSource != nullptr) {
        powerInfo = this->powerSource->getInfo();
    }

    return "Marka: " + getCarBrand() + ", Model: " + getCarModel() + ", NumerVIN: " + getVIN() + ", naped: " + powerInfo + ", wlasciciel: " + clientInfo;
}

bool Car::isArchive() const {
    return archive;
}

void Car::setArchive(bool arch) {
    archive = arch;
}
