/**
 * @file ClientManager.h
 * @brief Plik definiujący klasę ClientManager zarządzającą logiką biznesową klientów.
 */

#ifndef WARSZTATSAMOCHDOWY_CLIENTMANAGER_H
#define WARSZTATSAMOCHDOWY_CLIENTMANAGER_H

#include "../typedefs.h"
#include "repositories/ClientRepository.h"
#include <string>
#include <vector>

// Forward declaration
class ClientRepository;

/**
 * @class ClientManager
 * @brief Klasa zarządzająca operacjami na klientach.
 * @details Odpowiada za rejestrację, wyrejestrowanie oraz wyszukiwanie klientów w systemie.
 * Wykorzystuje ClientRepository do trwałego przechowywania danych.
 */
class ClientManager {
private:
    ClientRepository& clientRepository; /**<Referencja do repozytorium klientów. */
public:
    /**
     * @brief Konstruktor menedżera klientów.
     * @param repo Referencja do istniejącego repozytorium klientów.
     */
    ClientManager(ClientRepository& repo); // Konstruktor przyjmuje referencję do gotowego repozutorium

    /** @brief Destruktor domyślny. */
    ~ClientManager() = default;

    /**
     * @brief Pobiera klienta na podstawie numeru PESEL.
     * @param personalID Unikalny identyfikator PESEL.
     * @return ClientPtr Wskaźnik na klienta lub nullptr, jeśli nie znaleziono.
     */
    ClientPtr getClient(const std::string& personalID) const;

    /**
     * @brief Rejestruje nowego klienta w systemie.
     * @details Jeśli klient o podanym PESEL-u już istnieje, zwraca istniejący obiekt.
     * @param firstName Imię klienta.
     * @param lastName Nazwisko klienta.
     * @param phoneNumber Numer telefonu.
     * @param email email klienta.
     * @param personalID PESEL klienta.
     * @return ClientPtr Wskaźnik na nowo zarejestrowanego lub istniejącego klienta.
     */
    ClientPtr registerClient(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber, const std::string& email, const std::string& personalID);

    /**
     * @brief Wyrejestrowuje klienta (ustawia flagę archiwizacji).
     * @param client Wskaźnik na klienta do usunięcia z aktywnego użytku.
     */
    void unregisterClient(ClientPtr client);

    /**
     * @brief Wyszukuje klientów spełniających określone kryterium.
     * @param predicate Funkcja (lambda) definiująca warunek wyszukiwania.
     * @return std::vector<ClientPtr> Lista znalezionych klientów (niezarchiwizowanych).
     */
    std::vector<ClientPtr> findClients(ClientPredicate predicate) const;

    /**
     * @brief Pobiera listę wszystkich klientów w systemie.
     * @return std::vector<ClientPtr> Wektor wszystkich obiektów klientów.
     */
    std::vector<ClientPtr> findAllClients() const;
};

#endif //WARSZTATSAMOCHDOWY_CLIENTMANAGER_H