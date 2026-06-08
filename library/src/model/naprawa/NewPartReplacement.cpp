#include "model/naprawa/NewPartReplacement.h"

NewPartReplacement::NewPartReplacement(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin,
                                       const unsigned int &_partPrice) : TimeBasedService(_name, _hourPrice, _begin),
                                                                         newPartPrice(_partPrice) {
}

const unsigned int &NewPartReplacement::getNewPartPrice() const {
    return this->newPartPrice;
}

double NewPartReplacement::getServiceCost() const {
    return TimeBasedService::getServiceCost() + getNewPartPrice();
}

std::string NewPartReplacement::getInfo() const {
    return "Wymiana czesci, " + TimeBasedService::getInfo() + ", cena nowej czesci: " + std::to_string(
               getNewPartPrice());
}
