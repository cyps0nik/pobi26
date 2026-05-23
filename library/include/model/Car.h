#ifndef CARRENTAL_CAR_H
#define CARRENTAL_CAR_H
#include <string>

class Car {
private:
    std::string carBrand;
    std::string carModel;
    std::string VIN;
public:
    Car(std::string _carBrand, std::string _carModel, std::string _VIN);
    ~Car();
    const std::string& getCarBrand() const;
    const std::string& getCarModel() const;
    const std::string& getVIN() const;
    // setterow nie robie bo jak raz stworzy sie auto to z BMW
    // nie zmienia sie na mercedesa z VINem to samo
};


#endif //CARRENTAL_CAR_H