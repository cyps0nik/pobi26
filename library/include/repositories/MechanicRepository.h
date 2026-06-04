/**
 * @file MechanicRepository.h
 * @brief Definicja klasy MechanicRepository zarządzającej obiektami klasy Mechanic.
 */

#ifndef PROJECTPOBI_MECHANICREPOSITORY_H
#define PROJECTPOBI_MECHANICREPOSITORY_H

#include <vector>
#include <string>
#include "typedefs.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

/**
 * @brief Repozytorium przechowujące wskaźniki do obiektów klasy Mechanic.
 * @details Klasa umożliwia podstawowe operacje CRUD oraz zaawansowane wyszukiwanie za pomocą predykatów.
 */
class MechanicRepository {
private:
    /**
     * @brief Kolekcja inteligentnych wskaźników do obiektów klasy Mechanic.
     * @details Wykorzystuje std::vector dla zapewnienia szybkiego dostępu sekwencyjnego
     * i dynamicznego zarządzania rozmiarem bazy mechaników.
     */
    std::vector<MechanicPtr> mechanics;

    // Nadanie uprawnień Boostowi (do zaglądania w prywatne pola)
    friend class boost::serialization::access;

    // Metoda, która mówi Boostowi, co ma zapisać z tej klasy
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & mechanics;
    }

public:
    /**
     * @brief Konstruktor domyślny.
     * @details Inicjalizuje puste repozytorium mechaników.
     */
    MechanicRepository() = default;

    /**
     * @brief Destruktor klasy MechanicRepository.
     * @details Zwalnia zasoby zarządzane przez repozytorium.
     */
    ~MechanicRepository() = default;

    /**
     * @brief Pobiera Mechanika o określonym indeksie.
     * @param index Pozycja w repozytorium.
     * @return MechanicPtr Wskaźnik do mehchanika lub nullptr, jeśli indeks jest nieprawidłowy.
     */
    MechanicPtr get(int index) const;

    /**
     * @brief Dodaje mechanika do repozytorium.
     * @param mechanic Wskaźnik do dodawanego obiektu. Pomija nullptr.
     */
    void add(MechanicPtr mechanic);

    /**
     * @brief Usuwa mechanika z repozytorium.
     * @param mechanic Wskaźnik do mechanika, która ma zostać usunięty.
     */
    void remove(MechanicPtr mechanic);

    /**
     * @brief Generuje tekstowy raport o wszystkich mechanikach.
     * @return std::string Zbiorcze informacje o obiektach w repozytorium.
     */
    std::string report() const;

    /**
     * @brief Zwraca aktualną liczbę mechaników.
     * @return int Rozmiar kolekcji.
     */
    int size() const;

    /**
     * @brief Metoda wyszukująca obiekty spełniające podane kryterium (predykat).
     * @param predicate Funkcja lub lambda definiująca warunek wyszukiwania.
     * @return std::vector<MechanicPtr> Wektor wskaźników do znalezionych mechaników.
     */
    std::vector<MechanicPtr> findBy(MechanicPredicate predicate) const;

    /**
     * @brief Zwraca wszystkich mechaników znajdujących się w repozytorium.
     * @return std::vector<MechanicPtr> Wektor wszystkich obiektów.
     */
    std::vector<MechanicPtr> findAll() const;
};


#endif //PROJECTPOBI_MECHANICREPOSITORY_H