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
    Engine(int _engineDisplacement, FuelType _typPaliwa);
    ~Engine() = default;
    const int& getEngineDisplacement() const;
    const FuelType& getFuelType() const;
    double getMultiplier() const override;
};


#endif //WARSZTATSAMOCHDOWY_ENGINE_H
