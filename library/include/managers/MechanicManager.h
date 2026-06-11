/**
 * @file MechanicManager.h
 * @brief Plik definiujący klasę MechanicManager zarządzającą logiką biznesową mechaników.
 */

#ifndef WARSZTATSAMOCHDOWY_MECHANICMANAGER_H
#define WARSZTATSAMOCHDOWY_MECHANICMANAGER_H

#include "../typedefs.h"
#include "repositories/MechanicRepository.h"
#include <string>
#include <vector>

#include "model/naprawa/Mechanic.h"

// Forward declaration
class MechanicRepository;

/**
 * @class MechanicManager
 * @brief Klasa zarządzająca operacjami na mechanikach.
 * @details Odpowiada za rejestrację, wyrejestrowanie oraz wyszukiwanie mechaników w systemie.
 * Wykorzystuje MechanicRepository do trwałego przechowywania danych.
 */
class MechanicManager {
private:
    MechanicRepository& mechanicRepository; /**<Referencja do repozytorium mechaników. */
    unsigned int nextId = 1;                /**< Generator unikalnych numerów ID dla mechaników. */

public:
    /**
     * @brief Konstruktor menedżera mechaników.
     * @param repo Referencja do istniejącego repozytorium mechaników.
     */
    MechanicManager(MechanicRepository& repo); // Konstruktor przyjmuje referencję do gotowego repozutorium

    /** @brief Destruktor domyślny. */
    ~MechanicManager() = default;

    /**
     * @brief Pobiera mechanika na podstawie unikalnego ID.
     * @param id Identyfikator wyszukiwanego mechanika.
     * @return MechanicPtr Wskaźnik na mechanika lub nullptr, jeśli nie znaleziono.
     */
    MechanicPtr getMechanic(int id) const;

    /**
     * @brief Rejestruje nowego mechanika w systemie(zatrudnienie).
     * @details Jeśli mechanik o następnym ID już istnieje, zwraca istniejący obiekt.
     * @param firstName Imię mechanika.
     * @param lastName Nazwisko mechanika.
     * @param spec informacja o specyfikacji mechanika (elektryk, diagnosta...).
     * @return MechanicPtr Wskaźnik na nowo zarejestrowanego lub istniejącego mechanika.
     */
    MechanicPtr registerMechanic(const std::string& firstName, const std::string& lastName, const Specialization &spec);

    /**
     * @brief Wyrejestrowuje mechanika (ustawia flagę archiwizacji).
     * @param mechanic Wskaźnik na mechanika do usunięcia z aktywnego użytku.
     */
    void unregisterMechanic(MechanicPtr mechanic);

    /**
     * @brief Wyszukuje mechaników spełniających określone kryterium.
     * @param predicate Funkcja (lambda) definiująca warunek wyszukiwania.
     * @return std::vector<MechanicPtr> Lista znalezionych Mechaników (niezarchiwizowanych).
     */
    std::vector<MechanicPtr> findMechanics(MechanicPredicate predicate) const;

    /**
     * @brief Pobiera listę wszystkich mechaników w systemie.
     * @return std::vector<MechanicPtr> Wektor wszystkich obiektów mechaników.
     */
    std::vector<MechanicPtr> findAllMechanics() const;

    /**
     * @brief Wyszukuje mechaników, którzy nie są obecnie zajęci naprawą.
     * @return std::vector<MechanicPtr> Lista dostępnych mechaników.
     */
    std::vector<MechanicPtr> findAvailableMechanics() const;


};


#endif //WARSZTATSAMOCHDOWY_MECHANICMANAGER_H