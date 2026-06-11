/**
 * @file RepairManager.h
 * @brief Plik definiujący klasę RepairManager zarządzającą logiką biznesową napraw.
 */

#ifndef WARSZTATSAMOCHDOWY_REPAIRMANAGER_H
#define WARSZTATSAMOCHDOWY_REPAIRMANAGER_H

#include "../typedefs.h"
#include "repositories/RepairRepository.h"
#include <boost/date_time.hpp>
#include <string>
#include <vector>

// Forward declaration
class RepairRepository;

/**
 * @class RepairManager
 * @brief Klasa odpowiedzialna za zarządzanie procesami napraw samochodów w warsztacie.
 * @details Umożliwia rejestrację nowych zleceń naprawy, sprawdzanie ich statusów oraz
 * wyszukiwanie według zaawansowanych kryteriów (np. naprawy obecnie trwające).
 */
class RepairManager {
private:
    RepairRepository& repairRepository; /**< Referencja do repozytorium napraw. */
    unsigned int nextId = 1;            /**< Generator unikalnych numerów ID dla napraw. */
public:
    /**
     * @brief Konstruktor menedżera napraw.
     * @param repo Referencja do istniejącego repozytorium napraw.
     */
    RepairManager(RepairRepository& repo);

    /** @brief Destruktor domyślny. */
    ~RepairManager() = default;

    /**
     * @brief Pobiera naprawę na podstawie unikalnego ID.
     * @param id Identyfikator wyszukiwanej naprawy.
     * @return RepairPtr Wskaźnik na obiekt naprawy lub nullptr, jeśli nie znaleziono.
     */
    RepairPtr getRepair(int id) const;

    /**
     * @brief Tworzy nową naprawę w warsztacie.
     * @details Jeśli naprawa o następnym ID już istnieje, metoda zwraca istniejący obiekt.
     * @param beginTime Czas rozpoczęcia naprawy (zgodny z boost::posix_time::ptime).
     * @param car Wskaźnik na samochód, którego dotyczy naprawa.
     * @return RepairPtr Wskaźnik na utworzoną lub istniejącą już naprawę.
     */
    RepairPtr registerRepair(const boost::posix_time::ptime& beginTime, const CarPtr& car);

    /**
     * @brief Wyrejestrowuje naprawę (ustawia flagę archiwizacji).
     * @param repair Wskaźnik na naprawę do usunięcia.
     */
    void unregisterRepair(RepairPtr repair) const;

    /**
     * @brief Wyszukuje naprawy spełniające określone kryterium podane w predykacie.
     * @param predicate Funkcja (lambda) definiująca warunek filtrowania napraw.
     * @return std::vector<RepairPtr> Lista znalezionych napraw.
     */
    std::vector<RepairPtr> findRepairs(RepairPredicate predicate) const;

    /**
     * @brief Pobiera listę wszystkich napraw zarejestrowanych w systemie.
     * @return std::vector<RepairPtr> Wektor wszystkich obiektów napraw.
     */
    std::vector<RepairPtr> findAllRepairs() const;

    /**
     * @brief Wyszukuje aktywne naprawy, które są obecnie w toku (nie zostały zakończone).
     * @return std::vector<RepairPtr> Lista napraw, które aktualnie trwają w warsztacie.
     */
    std::vector<RepairPtr> findCurrentRepairs() const;
};


#endif //WARSZTATSAMOCHDOWY_REPAIRMANAGER_H