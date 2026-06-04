/**
 * @file CarRepository.cpp
 * @brief Implementacja metod zarządzania samochodami.
 */

#include "repositories/CarRepository.h"
#include "model/Car.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

CarRepository::~CarRepository() {}

CarPtr CarRepository::get(int index) const {
    if (index < 0 || index >= (int)cars.size()) return nullptr;
    return cars[index];
}

void CarRepository::add(CarPtr car) {
    if (car != nullptr) cars.push_back(car);
}

void CarRepository::remove(CarPtr car) {
    if (car != nullptr) {
        cars.erase(std::remove(cars.begin(), cars.end(), car), cars.end());
    }
}

std::string CarRepository::report() const {
    std::stringstream ss;
    for (CarPtr car : cars) {
        if (car != nullptr) ss << car->getInfo() << "\n";
    }
    return ss.str();
}

int CarRepository::size() const {
    return (int)cars.size();
}

std::vector<CarPtr> CarRepository::findBy(CarPredicate predicate) const {
    std::vector<CarPtr> found;
    for (unsigned int i = 0; i < cars.size(); i++) {
        CarPtr car = get(i);
        if (car != nullptr && predicate(car)) {
            found.push_back(car);
        }
    }
    return found;
}

std::vector<CarPtr> CarRepository::findAll() const {
    return findBy([](const CarPtr&) { return true; });
}

CarPtr CarRepository::findByVin(const std::string& vin) const {
    CarPredicate predicate = [vin](const CarPtr& c) {
        return c != nullptr && c->getVIN() == vin;
    };

    std::vector<CarPtr> found = findBy(predicate);
    if (found.empty()) {
        return nullptr;
    }
    else{
        return found[0];
    }
}

