#include "model/naprawa/PartRegenaration.h"

PartRegenaration::PartRegenaration(const std::string &_name, const int &_hourPrice, const pt::ptime &_begin,
                                   const int &_usage) : TimeBasedService(_name, _hourPrice, _begin) {
    if (_usage < 0 || _usage > 100) throw std::invalid_argument("Zuzycie czesci ma zakres od 0 do 100 %");
    else this->usage = _usage;
}

const int &PartRegenaration::getUsage() const {
    return this->usage;
}

std::string PartRegenaration::getInfo() const {
    return "Regeneracja czesci, " + TimeBasedService::getInfo() + ", procent zuzycia: " + std::to_string(getUsage()) + "%";
}

double PartRegenaration::getServiceCost() const {
    double mnoznik;
    if (getUsage() <= 25) {
        mnoznik = 1.0 + getUsage() * (0.2 / 25.0);
    } else if (getUsage() <= 50) mnoznik = 1.5;
    else {
        mnoznik = 1.5 + (getUsage() - 50.0) * (0.5 / 50.0);
    }
    return TimeBasedService::getServiceCost() * mnoznik;
}
