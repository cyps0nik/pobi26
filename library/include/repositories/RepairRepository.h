//
// Created by marek on 4.06.2026.
//

#ifndef PROJECTPOBI_REPAIRREPOSITORY_H
#define PROJECTPOBI_REPAIRREPOSITORY_H

#include <vector>
#include <string>
#include "typedefs.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

/**
 * @brief Repozytorium przechowujące wskaźniki do obiektów klasy Repair.
 * @details Klasa umożliwia podstawowe operacje CRUD oraz zaawansowane wyszukiwanie za pomocą predykatów.
 */
class RepairRepository {
private:
    /**
     * @brief Kolekcja inteligentnych wskaźników do obiektów klasy Repair.
     * @details Wykorzystuje std::vector dla zapewnienia szybkiego dostępu sekwencyjnego
     * i dynamicznego zarządzania rozmiarem bazy napraw.
     */
    std::vector<RepairPtr> repairs;

    // Nadanie uprawnień Boostowi (do zaglądania w prywatne pola)
    friend class boost::serialization::access;

    // Metoda, która mówi Boostowi, co ma zapisać z tej klasy
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & repairs;
    }

public:
    /**
     * @brief Konstruktor domyślny.
     * @details Inicjalizuje puste repozytorium napraw.
     */
    RepairRepository() = default;

    /**
     * @brief Destruktor klasy RepairRepository.
     * @details Zwalnia zasoby zarządzane przez repozytorium.
     */
    ~RepairRepository() = default;

    /**
     * @brief Pobiera naprawę o określonym indeksie.
     * @param index Pozycja w repozytorium.
     * @return RepairPtr Wskaźnik do naprawy lub nullptr, jeśli indeks jest nieprawidłowy.
     */
    RepairPtr get(int index) const;

    /**
     * @brief Dodaje naprawę do repozytorium.
     * @param repair Wskaźnik do dodawanego obiektu. Pomija nullptr.
     */
    void add(RepairPtr repair);

    /**
     * @brief Usuwa naprawę z repozytorium.
     * @param repair Wskaźnik do naprawę, która ma zostać usunięta.
     */
    void remove(RepairPtr repair);

    /**
     * @brief Generuje tekstowy raport o wszystkich naprawach.
     * @return std::string Zbiorcze informacje o obiektach w repozytorium.
     */
    std::string report() const;

    /**
     * @brief Zwraca aktualną liczbę napraw.
     * @return int Rozmiar kolekcji.
     */
    int size() const;

    /**
     * @brief Metoda wyszukująca obiekty spełniające podane kryterium (predykat).
     * @param predicate Funkcja lub lambda definiująca warunek wyszukiwania.
     * @return std::vector<RepairPtr> Wektor wskaźników do znalezionych napraw.
     */
    std::vector<RepairPtr> findBy(RepairPredicate predicate) const;

    /**
     * @brief Zwraca wszystkie naprawy znajdujących się w repozytorium.
     * @return std::vector<RepairPtr> Wektor wszystkich obiektów.
     */
    std::vector<RepairPtr> findAll() const;

    /**
     * @brief Wyszukuje naprawę na podstawie id.
     * @param id stała reprezentująca id naprawy.
     * @return RepairPtr Wskaźnik do znalezioną naprawę lub nullptr, jeśli nie istnieje.
     */
    RepairPtr findById(int id) const;
};


#endif //PROJECTPOBI_REPAIRREPOSITORY_H