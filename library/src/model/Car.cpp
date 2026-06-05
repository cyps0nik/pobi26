#include "model/Car.h"
#include "model/PoweredBy.h"
#include <utility>
#include <string>
Car::Car(const std::string &_carBrand, const std::string &_carModel, const std::string &_VIN,  PoweredUniqPtr _power
    , const ClientPtr &_owner) : carBrand(_carBrand), carModel(_carModel), VIN(_VIN), powerSource(std::move(_power)), owner(_owner) {

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

PoweredBy*Car::getPowerSource() const {
    return this->powerSource.get();
}

std::string Car::getInfo() const {
    std::string info = "Marka: " + getCarBrand() + ", Model: " + getCarModel() + ", NumerVIN: " + getVIN();
    info += ", Napęd: nic, Właściciel: nullptr";
    return info;
}





