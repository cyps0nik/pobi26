#ifndef WARSZTATSAMOCHDOWY_ACCUMULATOR_H
#define WARSZTATSAMOCHDOWY_ACCUMULATOR_H
#include "PoweredBy.h"

class Accumulator : public PoweredBy {
private:
    int capacityKWh;
    int degradationLevel;
public:
    Accumulator(const int& _capacityKWh, const int& _degradationLevel);
    const int& getCapacityKWh() const;
    const int& getDegradationLevel() const;
    double getMultiplier() const override;
};


#endif //WARSZTATSAMOCHDOWY_ACCUMULATOR_H
