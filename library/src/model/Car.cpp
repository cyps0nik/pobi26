#include "model/Car.h"
#include "model/Car.h"
Car::Car(std::string _carBrand, std::string _carModel, std::string _VIN) {
    this->carBrand = _carBrand;
    this->carModel = _carModel;
    this->VIN = _VIN;
}
Car::~Car() {}
const std::string &Car::getCarBrand() const {
    return this->carBrand;
}
const std::string &Car::getCarModel() const {
    return this->carModel;
}
const std::string &Car::getVIN() const {
    return this->VIN;
}
const std::unique_ptr<PoweredBy> &Car::getPoweredBy() const {
    return this->zasilanie;
}



