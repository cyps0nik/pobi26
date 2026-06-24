#include "model/naprawa/DiagnosticService.h"
#include <stdexcept>

DiagnosticService::DiagnosticService(const std::string &_name, const int &_price,
                                     const ResourceAbstractionPtr &_resource,
                                     const MechanicAbstractionPtr &_mechanic) : Service(_name, _resource, _mechanic),
    fixedPrice(_price) {
    if (_price < 0) throw std::invalid_argument("Cena nie moze byc ujemna!");
    this->setRepaired(true);
}


std::string DiagnosticService::getInfo() const {
    return "Diagnostyczny serwis, " + Service::getInfo() + "cena: " + std::to_string(getServiceCost());
}

double DiagnosticService::getServiceCost() const {
    return this->fixedPrice;
}

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT(DiagnosticService)