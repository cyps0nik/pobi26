#ifndef CARRENTAL_CAR_H
#define CARRENTAL_CAR_H
#include <memory>
#include <string>

#include "typedefs.h"
#include "model/PoweredBy.h"
class Car {
private:
    std::string carBrand;
    std::string carModel;
    std::string VIN;
    PoweredUniqPtr powerSupply;
    ClientPtr owner;
public:
    Car(std::string _carBrand, std::string _carModel, std::string _VIN, PoweredUniqPtr _power, ClientPtr _owner);
    ~Car() = default;
    const std::string& getCarBrand() const;
    const std::string& getCarModel() const;
    const std::string& getVIN() const;
    const PoweredUniqPtr& getPowerSupply() const; //zeby moc uzyc tu abstrakcyjnej klasy
    // korzystamy z unique_ptr
    // setterow nie robie bo jak raz stworzy sie auto to z BMW
    // nie zmienia sie na mercedesa z VINem to samo
};


#endif //CARRENTAL_CAR_H