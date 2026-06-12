/**
 * @file StorageContainer.h
 * @brief Klasa agregująca wszystkie repozytoria systemu (Data Storage).
 * @details Pełni rolę centralnego kontenera na dane, zarządzając cyklem życia
 * repozytoriów dla klientów, samochodów, napraw, zasobów i mechaników.
 */

#ifndef PROJECTPOBI_STORAGECONTAINER_H
#define PROJECTPOBI_STORAGECONTAINER_H

#include "repositories/ClientRepository.h"
#include "repositories/CarRepository.h"
#include "repositories/MechanicRepository.h"
#include "repositories/RepairRepository.h"
#include "repositories/ResourceRepository.h"

#include <boost/serialization/access.hpp>

/**
 * @class StorageContainer
 * @brief Główny magazyn danych aplikacji.
 * @details Klasa ta zapewnia dostęp do wszystkich repozytoriów. W jej konstruktorze
 * następuje wstępne wypełnienie bazy danych (seeding) obiektami testowymi.
 */
class StorageContainer {
private:
    /** @brief Instancja repozytorium przechowująca dane wszystkich klientów. */
    ClientRepository clientRepository;

    /** @brief Instancja repozytorium przechowująca dane o wszystkich samochodach. */
    CarRepository carRepository;

    /** @brief Instancja repozytorium przechowująca dane o wszystkich mechanikach. */
    MechanicRepository mechanicRepository;

    /** @brief Instancja repozytorium przechowująca dane o wszystkich naprawach. */
    RepairRepository repairRepository;

    /** @brief Instancja repozytorium przechowująca dane o wszystkich zasobach. */
    ResourceRepository resourceRepository;

    // Nadanie uprawnień Boostowi
    friend class boost::serialization::access;

    // Metoda szablonowa łącząca wszystkie repozytoria w jeden proces zapisu/odczytu
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & clientRepository;
        ar & carRepository;
        ar & mechanicRepository;
        ar & repairRepository;
        ar & resourceRepository;
    }

public:
    /**
     * @brief Konstruktor inicjalizujący repozytoria i wypełniający je danymi startowymi.
     * @details Tworzy początkowy zestaw klientów i pojazdów, aby umożliwić natychmiastowe testowanie systemu.
     */
    StorageContainer();

    /** @brief Destruktor domyślny. */
    ~StorageContainer() = default;

    // GETTERY DO REPÓW

    /**
     * @brief Zwraca referencję do repozytorium klientów.
     * @return ClientRepository& Referencja do oryginalnej instancji repozytorium.
     */
    ClientRepository& getClientRepository();

    /**
     * @brief Zwraca referencję do repozytorium samochodów.
     * @return CarRepository& Referencja do oryginalnej instancji repozytorium.
     */
    CarRepository& getCarRepository();

    /**
     * @brief Zwraca referencję do repozytorium mechaników.
     * @return MechanicRepository& Referencja do oryginalnej instancji repozytorium.
     */
    MechanicRepository& getMechanicRepository();

    /**
     * @brief Zwraca referencję do repozytorium napraw.
     * @return RepairRepository& Referencja do oryginalnej instancji repozytorium.
     */
    RepairRepository& getRepairRepository();

    /**
     * @brief Zwraca referencję do repozytorium zasobów.
     * @return ResourceRepository& Referencja do oryginalnej instancji repozytorium.
     */
    ResourceRepository& getResourceRepository();



    /*     <-----Ładowanie i zczytywanie z/do pliku----->     */


    /**
     * @brief Zapisuje cały stan warsztatu (wszystkie repozytoria) do jednego pliku.
     * @param filename Nazwa pliku (np. "warsztat_data.txt").
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Wczytuje cały stan warsztatu z pliku.
     * @param filename Nazwa pliku.
     */
    void loadFromFile(const std::string& filename);
};


#endif //PROJECTPOBI_STORAGECONTAINER_H