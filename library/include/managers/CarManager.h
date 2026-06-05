/**
 * @file CarManager.h
 * @brief Plik nagłówkowy menedżera samochodów.
 */

#ifndef WARSZTATSAMOCHDOWY_CARMANAGER_H
#define WARSZTATSAMOCHDOWY_CARMANAGER_H

#include "typedefs.h"
#include "repositories/CarRepository.h"
#include <string>
#include <vector>

//Forward declaration
class CarRepository;

/**
 * @class CarManager
 * @brief Klasa odpowiedzialna za zarządzanie samochodami.
 */
class CarManager {
private:
    CarRepository& carRepository; /**<Referencja do repozytorium klientów. */
public:
    /**
    * @brief Konstruktor menedżera samochodów.
    * @param repo Referencja do istniejącego repozytorium aut.
    */
    CarManager(CarRepository& repo); // Kostruktor przyjmuje referencję do gotowego repozutorium

    /** @brief Destruktor domyślny. */
    ~CarManager() = default;

    /**
     * @brief Pobiera samochów na podstawie numeru VIN.
     * @param vin Unikalny ndmer VIN pojazdu.
     * @return CarPtr Wskaźnik na samochód lub nullptr, jeśli nie znaleziono.
     */
    CarPtr getCar(const std::string& vin) const;

    /**
     * @brief Rejestruje nowy samochód w systemie.
     * @details Jeśli auto o podanym numerze VIN już istnieje, zwraca istniejący obiekt.
     * @param brand marka pojazdu.
     * @param model model pojazdu.
     * @param vin numer vin auta.
     * @param power wskaźnik na typ napędu.
     * @param owner wskaźnik na właściciela pojazdu.
     * @return CarPtr Wskaźnik na nowo zarejestrowane lub istniejące auto.
     */
    CarPtr registerCar(const std::string& brand, const std::string& model, const std::string& vin, PoweredUniqPtr power, ClientPtr owner);

    /**
     * @brief Wyrejestrowuje pojazd (ustawia flagę archiwizacji).
     * @param car Wskaźnik na auto do usunięcia z aktywnego użytku.
     */
    void unregisterCar(CarPtr car);

    /**
     * @brief Wyszukuje samochody spełniające określone kryterium.
     * @param predicate Funkcja (lambda) definiująca warunek wyszukiwania.
     * @return std::vector<CarPtr> Lista znalezionych samochodów (niezarchiwizowanych).
     */
    std::vector<CarPtr> findCars(CarPredicate predicate) const;
};


#endif //WARSZTATSAMOCHDOWY_CARMANAGER_H