#ifndef CARRENTAL_CAR_H
#define CARRENTAL_CAR_H
#include <memory>
#include <string>
#include "model/PoweredBy.h"
class Car {
private:
    std::string carBrand;
    std::string carModel;
    std::string VIN;
    std::unique_ptr<PoweredBy> zasilanie;
public:
    Car(std::string _carBrand, std::string _carModel, std::string _VIN);
    ~Car();
    const std::string& getCarBrand() const;
    const std::string& getCarModel() const;
    const std::string& getVIN() const;
    const std::unique_ptr<PoweredBy>& getPoweredBy() const; //zeby moc uzyc tu abstrakcyjnej klasy
    //korzystamy z unique_ptr
    // setterow nie robie bo jak raz stworzy sie auto to z BMW
    // nie zmienia sie na mercedesa z VINem to samo
};


#endif //CARRENTAL_CAR_H