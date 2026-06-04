/**
 * @file CarRepository.h
 * @brief Definicja klasy CarRepository zarządzającej obiektami klasy Car.
 */

#ifndef PROJECTPOBI_CARREPOSITORY_H
#define PROJECTPOBI_CARREPOSITORY_H

#include <vector>
#include <string>
#include "typedefs.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

/**
 * @brief Repozytorium przechowujące wskaźniki do obiektów klasy Car.
 * @details Klasa umożliwia podstawowe operacje CRUD oraz zaawansowane wyszukiwanie za pomocą predykatów.
 */
class CarRepository {
private:
    /**
     * @brief Kolekcja inteligentnych wskaźników do obiektów klasy Car.
     * @details Wykorzystuje std::vector dla zapewnienia szybkiego dostępu sekwencyjnego
     * i dynamicznego zarządzania rozmiarem bazy samochodów.
     */
    std::vector<CarPtr> cars;

    // Nadanie uprawnień Boostowi (do zaglądania w prywatne pola)
    friend class boost::serialization::access;

    // Metoda, która mówi Boostowi, co ma zapisać z tej klasy
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & cars;
    }

public:
    /**
     * @brief Konstruktor domyślny.
     * @details Inicjalizuje puste repozytorium samochodów.
     */
    CarRepository() = default;

    /**
     * @brief Destruktor klasy CarRepository.
     * @details Zwalnia zasoby zarządzane przez repozytorium.
     */
    ~CarRepository() = default;

    /**
     * @brief Pobiera samochód o określonym indeksie.
     * @param index Pozycja w repozytorium.
     * @return CarPtr Wskaźnik do auta lub nullptr, jeśli indeks jest nieprawidłowy.
     */
    CarPtr get(int index) const;

    /**
     * @brief Dodaje samochów do repozytorium.
     * @param car Wskaźnik do dodawanego obiektu. Pomija nullptr.
     */
    void add(CarPtr car);

    /**
     * @brief Usuwa samochów z repozytorium.
     * @param car Wskaźnik do pojazdu, który ma zostać usunięty.
     */
    void remove(CarPtr car);

    /**
     * @brief Generuje tekstowy raport o wszystkich samochodach.
     * @return std::string Zbiorcze informacje o obiektach w repozytorium.
     */
    std::string report() const;

    /**
     * @brief Zwraca aktualną liczbę samochodów.
     * @return int Rozmiar kolekcji.
     */
    int size() const;

    /**
     * @brief Metoda wyszukująca samochody spełniające podane kryterium.
     * @param predicate Funkcja/lambda testująca obiekty Car.
     * @return std::vector<CarPtr> Lista znalezionych samochodów.
     */
    std::vector<CarPtr> findBy(CarPredicate predicate) const;

    /**
     * @brief Zwraca wszystkie samochody z repozytorium.
     * @return std::vector<CarPtr> Pełna lista samochodów.
     */
    std::vector<CarPtr> findAll() const;

    /**
     * @brief Wyszukuje samochód na podstawie numeru VIN.
     * @param vin Numer VIN samochodu.
     * @return CarPtr Wskaźnik do samochodu lub nullptr.
     * @details Kluczowe dla unikania duplikacji aut w systemie.
     */
    CarPtr findByVin(const std::string& vin) const;
};


#endif //PROJECTPOBI_CARREPOSITORY_H