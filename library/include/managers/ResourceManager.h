/**
 * @file ResourceManager.h
 * @brief Plik definiujący klasę ResourceManager zarządzającą logiką biznesową zasobów.
 */

#ifndef WARSZTATSAMOCHDOWY_RESOURCEMANAGER_H
#define WARSZTATSAMOCHDOWY_RESOURCEMANAGER_H

#include "typedefs.h"
#include "repositories/ResourceRepository.h"
#include <string>
#include <vector>

// Forward declaration
class ResourceRepository;

/**
 * @class ResourceManager
 * @brief Klasa zarządzająca operacjami na zasobach (np. stanowiskach, narzędziach).
 * @details Odpowiada za rejestrację, wyrejestrowanie oraz wyszukiwanie zasobów w systemie.
 * Wykorzystuje ResourceRepository do trwałego przechowywania danych w pamięci.
 */
class ResourceManager {
private:
    ResourceRepository& resourceRepository; /**< Referencja do repozytorium zasobów. */
public:
    /**
     * @brief Konstruktor menedżera zasobów.
     * @param repo Referencja do istniejącego repozytorium zasobów.
     */
    ResourceManager(ResourceRepository& repo);

    /** @brief Destruktor domyślny. */
    ~ResourceManager() = default;

    /**
     * @brief Pobiera zasób na podstawie unikalnego ID.
     * @param id Identyfikator wyszukiwanego zasobu.
     * @return ResourcePtr Wskaźnik na zasób lub nullptr, jeśli nie znaleziono.
     */
    //ResourcePtr getResource(int id) const;

    /**
     * @brief Rejestruje nowy zasób w systemie.
     * @details Jeśli zasób o podanym ID już istnieje, zwraca istniejący obiekt.
     * @param id Unikalny identyfikator zasobu.
     * @param name Nazwa lub opis zasobu (np. "Stanowisko podnośnikowe 1").
     * @return ResourcePtr Wskaźnik na nowo zarejestrowany lub istniejący zasób.
     */
    //ResourcePtr registerResource(int id, const std::string& name);

    /**
     * @brief Wyrejestrowuje zasób (ustawia flagę archiwizacji).
     * @param resource Wskaźnik na zasób do usunięcia z aktywnego użytku.
     */
    void unregisterResource(ResourcePtr resource);

    /**
     * @brief Wyszukuje zasoby spełniające określone kryterium.
     * @param predicate Funkcja (lambda) definiująca warunek wyszukiwania.
     * @return std::vector<ResourcePtr> Lista znalezionych zasobów (niezarchiwizowanych).
     */
    std::vector<ResourcePtr> findResources(ResourcePredicate predicate) const;

    /**
     * @brief Pobiera listę wszystkich aktywnych zasobów w systemie.
     * @return std::vector<ResourcePtr> Wektor wszystkich aktywnych obiektów zasobów.
     */
    std::vector<ResourcePtr> findAllResources() const;

    /**
     * @brief Wyszukuje zasoby, które są obecnie wolne i gotowe do użycia.
     * @return std::vector<ResourcePtr> Lista dostępnych (niezajętych) zasobów.
     */
    std::vector<ResourcePtr> findAvailableResources() const;
};


#endif //WARSZTATSAMOCHDOWY_RESOURCEMANAGER_H