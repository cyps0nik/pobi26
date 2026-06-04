#include "model/Engine.h"
#include <stdexcept> //potrzeben do throw

Engine::Engine(const int &_engineDisplacement, FuelType _typPaliwa) {
    if (_engineDisplacement < 0) throw std::invalid_argument("Pojemnosc nie moze byc ujemna");
    else this->engineDisplacement = _engineDisplacement;
    this->typPaliwa = _typPaliwa;
}



const int &Engine::getEngineDisplacement() const {
    return this->engineDisplacement;
}
const FuelType &Engine::getFuelType() const {
    return this->typPaliwa;
}

double Engine::getMultiplier() const {
    double mnoznik;
    if (this->engineDisplacement <= 0) mnoznik = 0;
    else if(this->engineDisplacement < 1000) mnoznik = 1.0;
    else if (this->engineDisplacement <= 2000) {
        mnoznik = this->engineDisplacement * 0.0005 + 0.5;
    }
    else if (this->engineDisplacement <= 6000) {
        mnoznik = this->engineDisplacement * 0.000375 + 0.75;
    }
    else mnoznik = 3.0;
    if (this->typPaliwa == Diesel) mnoznik *= this->typPaliwa/10.0;
    return mnoznik;
}


