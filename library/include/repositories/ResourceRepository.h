/**
* @file ResourceRepository.h
 * @brief Definicja klasy ResourceRepository zarządzającej obiektami klasy Resource.
 */

#ifndef PROJECTPOBI_RESOURCEREPOSITORY_H
#define PROJECTPOBI_RESOURCEREPOSITORY_H

#include <vector>
#include <string>
#include "typedefs.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

/**
 * @brief Repozytorium przechowujące wskaźniki do obiektów klasy Resource.
 * @details Klasa umożliwia podstawowe operacje CRUD oraz zaawansowane wyszukiwanie za pomocą predykatów.
 */
class ResourceRepository {
private:
    /**
     * @brief Kolekcja inteligentnych wskaźników do obiektów klasy Resource.
     * @details Wykorzystuje std::vector dla zapewnienia szybkiego dostępu sekwencyjnego
     * i dynamicznego zarządzania rozmiarem bazy zasobów.
     */
    std::vector<ResourcePtr> resources;

    // Nadanie uprawnień Boostowi (do zaglądania w prywatne pola)
    friend class boost::serialization::access;

    // Metoda, która mówi Boostowi, co ma zapisać z tej klasy
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & resources;
    }

public:
    /**
     * @brief Konstruktor domyślny.
     * @details Inicjalizuje puste repozytorium zasobów.
     */
    ResourceRepository() = default;

    /**
     * @brief Destruktor klasy ResourceRepository.
     * @details Zwalnia zasoby zarządzane przez repozytorium.
     */
    ~ResourceRepository() = default;

    /**
     * @brief Pobiera zasób o określonym indeksie.
     * @param index Pozycja w repozytorium.
     * @return ResourcePtr Wskaźnik do zasobu lub nullptr, jeśli indeks jest nieprawidłowy.
     */
    ResourcePtr get(int index) const;

    /**
     * @brief Dodaje zasób do repozytorium.
     * @param resource Wskaźnik do dodawanego obiektu. Pomija nullptr.
     */
    void add(ResourcePtr resource);

    /**
     * @brief Usuwa dany zasób z repozytorium.
     * @param resource Wskaźnik do zasób, który ma zostać usunięty.
     */
    void remove(ResourcePtr resource);

    /**
     * @brief Generuje tekstowy raport o wszystkich zasobach.
     * @return std::string Zbiorcze informacje o obiektach w repozytorium.
     */
    std::string report() const;

    /**
     * @brief Zwraca aktualną liczbę zasobów.
     * @return int Rozmiar kolekcji.
     */
    int size() const;

    /**
     * @brief Metoda wyszukująca obiekty spełniające podane kryterium (predykat).
     * @param predicate Funkcja lub lambda definiująca warunek wyszukiwania.
     * @return std::vector<ResourcePtr> Wektor wskaźników do znalezionych zasobów.
     */
    std::vector<ResourcePtr> findBy(ResourcePredicate predicate) const;

    /**
     * @brief Zwraca wszystkie zasoby znajdujących się w repozytorium.
     * @return std::vector<ResourcePtr> Wektor wszystkich obiektów.
     */
    std::vector<ResourcePtr> findAll() const;

    /**
     * @brief Wyszukuje zasób na podstawie id.
     * @param id stała reprezentująca id zasobu.
     * @return ResourcePtr Wskaźnik do znaleziony zasób lub nullptr, jeśli nie istnieje.
     */
    ResourcePtr findById(int id) const;
};


#endif //PROJECTPOBI_RESOURCEREPOSITORY_H