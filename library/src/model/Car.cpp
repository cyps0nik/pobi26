#include "model/Car.h"
Car::Car(std::string _carBrand, std::string _carModel, std::string _VIN, PoweredUniqPtr _power, ClientPtr _owner) {
    this->carBrand = _carBrand;
    this->carModel = _carModel;
    this->VIN = _VIN;
    this->powerSupply = (std::move(_power));
    this->owner = _owner;
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

PoweredUniqPtr Car::getPowerSupply() const {
    return this->powerSupply;
}
const ClientPtr &Car::getOwner() const {
    return this->owner;
}




