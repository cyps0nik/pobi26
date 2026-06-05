/**
* @file CarManager.cpp
 * @brief Implementacja logiki zarządzania samochodami.
 * @details Zawiera definicje metod odpowiedzialnych za rejestrację nowych aut,
 * ich wyszukiwanie w repozytorium oraz bezpieczne wyrejestrowywanie (archiwizację).
 */

#include "../../include/managers/CarManager.h"
#include "repositories/CarRepository.h"
#include "model/Car.h"

using namespace std;

CarManager::CarManager(CarRepository& repo) : carRepository(repo) {}

CarPtr CarManager::getCar(const string& vin) const {
    // Delegacja odpowiedzialności do repozytorium
    return carRepository.findByVin(vin);
}

CarPtr CarManager::registerCar(const string& brand, const string& model, const string& vin, PoweredUniqPtr power, ClientPtr owner) {
    // 1. Sprawdzamy, czy samochód już istnieje
    CarPtr existing = getCar(vin);
    if (existing != nullptr) return existing;

    // 2. Jeśli nie istnieje, tworzymy nowy
    CarPtr newCar = make_shared<Car>(brand, model, vin, std::move(power), owner);
    // 3. Dodajemy do repozytorium
    carRepository.add(newCar);
    return newCar;
}

void CarManager::unregisterCar(CarPtr car) {
    if (car != nullptr) {
        // Sprawdzamy, czy auto jest w repozytorium
        CarPtr found = getCar(car->getVIN());
        if (found != nullptr) {
            found->setArchive(true);
        }
    }
}

std::vector<CarPtr> CarManager::findCars(CarPredicate predicate) const {
    return carRepository.findBy([predicate](const CarPtr& c) {
        return c != nullptr && predicate(c) && !c->isArchive();
    });
}

