/**
 * @file MechanicManager.h
 * @brief Plik definiujący klasę MechanicManager zarządzającą logiką biznesową mechaników.
 */

#ifndef WARSZTATSAMOCHDOWY_MECHANICMANAGER_H
#define WARSZTATSAMOCHDOWY_MECHANICMANAGER_H

#include "typedefs.h"
#include "repositories/MechanicRepository.h"
#include <string>
#include <vector>

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
    MechanicRepository& mechanicRepository; /**<Referencja do repozytorium klientów. */
public:
    /**
    * @brief Konstruktor menedżera mechaników.
    * @param repo Referencja do istniejącego repozytorium mechaników.
    */
    MechanicManager(MechanicRepository& repo);

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
     * @details Jeśli mechanik o podanym ID już istnieje, zwraca istniejący obiekt.
     * @param firstName Imię mechanika.
     * @param lastName Nazwisko mechanika.
     * @param id uniwersalne id mechanika.
     * @param isBusy stan zajętości/pracy mechanika.
     * @param hasEVCertificate informacja o certyfikacie mechanika.
     * @return MechanicPtr Wskaźnik na nowo zarejestrowanego lub istniejącego mechanika.
     */
    MechanicPtr registerMechanic(const std::string& firstName, const std::string& lastName, int id, bool isBusy, bool hasEVCertificate);

    /**
     * @brief Wyrejestrowuje mechanika (ustawia flagę archiwizacji).
     * @param mechanc Wskaźnik na mechanika do usunięcia z aktywnego użytku.
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
     * @return std::vector<MechanikPtr> Wektor wszystkich obiektów mechaników.
     */
    std::vector<MechanicPtr> findAllMechanics() const;

    /**
     * @brief Wyszukuje mechaników, którzy nie są obecnie zajęci naprawą.
     * @return std::vector<MechanicPtr> Lista dostępnych mechaników.
     */
    std::vector<MechanicPtr> findAvailableMechanics() const;

    /**
     * @brief Wyszukuje mechaników posiadających certyfikat do obsługi pojazdów elektrycznych.
     * @return std::vector<MechanicPtr> Lista certyfikowanych mechaników.
     */
    std::vector<MechanicPtr> findMechanicsWithEVCertificate() const;
};


#endif //WARSZTATSAMOCHDOWY_MECHANICMANAGER_H