#include "model/Accumulator.h"
Accumulator::Accumulator(int _capacityKWh, int _degradationLevel) {
    if (_capacityKWh < 0) return;
    else this->capacityKWh = _capacityKWh;
    if (_degradationLevel < 0 || degradationLevel > 100) return;
    else this->degradationLevel = _degradationLevel;
}
const int &Accumulator::getCapacityKWh() const {
    return this->capacityKWh;
}
const int &Accumulator::getDegradationLevel() const {
    return this->degradationLevel;
}
double Accumulator::getMultiplier() const {
    int mnoznik;
    if (capacityKWh < 40) mnoznik = 1.0;
    else if (capacityKWh <= 100) {
    mnoznik = 1.0 + (this->capacityKWh - 40.0) * (0.8 / 60.0);
    }
    else mnoznik = 2.5;
    if (this->degradationLevel > 20) mnoznik += 0.3;
    return mnoznik;
}



