#ifndef WARSZTATSAMOCHDOWY_ENGINE_H
#define WARSZTATSAMOCHDOWY_ENGINE_H
#include "PoweredBy.h"
enum FuelType {
    Petrol = 10,
    Diesel = 12
};
class Engine : public PoweredBy {
private:
    int engineDisplacement;
    FuelType typPaliwa;
public:
    Engine(const int& _engineDisplacement, const FuelType& _typPaliwa);
    const int& getEngineDisplacement() const;
    const FuelType& getFuelType() const;
    double getMultiplier() const override;
};


#endif //WARSZTATSAMOCHDOWY_ENGINE_H
