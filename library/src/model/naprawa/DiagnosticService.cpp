#include "model/naprawa/DiagnosticService.h"
#include <stdexcept>

DiagnosticService::DiagnosticService(const std::string &_name, const int &_price) : Service(_name) {
    if (_price < 0) throw std::invalid_argument("Cena nie moze byc ujemna!");
    else this->fixedPrice = _price;
}

std::string DiagnosticService::getInfo() const {
    return "Diagnostyczny serwis, " + Service::getInfo() + "cena: " + std::to_string(getServiceCost());
}

int DiagnosticService::getServiceCost() const {
    return this->fixedPrice;
}
