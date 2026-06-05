#ifndef CARRENTAL_CAR_H
#define CARRENTAL_CAR_H
#include <memory>
#include <string>

#include "typedefs.h"

class Car {
private:
    std::string carBrand;
    std::string carModel;
    std::string VIN;
    PoweredUniqPtr powerSource;
    ClientPtr owner;

public:
    Car(const std::string &_carBrand, const std::string &_carModel, const std::string &_VIN, PoweredUniqPtr _power,
        const ClientPtr &_owner);

    ~Car() = default;

    const std::string &getCarBrand() const;

    const std::string &getCarModel() const;

    const std::string &getVIN() const;

    PoweredBy *getPowerSource() const; //zeby moc uzyc tu abstrakcyjnej klasy

    // korzystamy z unique_ptr
    // setterow nie robie bo jak raz stworzy sie auto to z BMW
    // nie zmienia sie na mercedesa z VINem to samo

    /**
     * @brief Zwraca podstawowe informacje o samochodzie.
     * @return std::string Ciąg znaków: Marka, Model, Numer VIN, Napęd, Właściciel.
     */
    std::string getInfo() const;
};


#endif //CARRENTAL_CAR_H
