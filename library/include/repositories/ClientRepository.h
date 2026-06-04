/**
 * @file ClientRepository.h
 * @brief Definicja klasy ClientRepository zarządzającej obiektami klasy Client.
 */

#ifndef PROJECTPOBI_CLIENTREPOSITORY_H
#define PROJECTPOBI_CLIENTREPOSITORY_H

#include <vector>
#include <string>
#include "typedefs.h"

#include <boost/serialization/access.hpp> // Daje dostęp do głównego mechanizmu serializacji Boosta
#include <boost/serialization/vector.hpp> // Automatyczne serializowanie(zapisywanie i odczytywanie) std::vector
#include <boost/serialization/shared_ptr.hpp> // Automatyczne obsługiwanie sprytnych wskażników

/**
 * @brief Repozytorium przechowujące wskaźniki do obiektów klasy Client.
 * @details Klasa umożliwia podstawowe operacje CRUD oraz zaawansowane wyszukiwanie za pomocą predykatów.
 */
class ClientRepository {
private:
    /**
     * @brief Kolekcja inteligentnych wskaźników do obiektów klasy Client.
     * @details Wykorzystuje std::vector dla zapewnienia szybkiego dostępu sekwencyjnego
     * i dynamicznego zarządzania rozmiarem bazy klientów.
     */
    std::vector<ClientPtr> clients;

    // Nadanie uprawnień Boostowi (do zaglądania w prywatne pola)
    friend class boost::serialization::access;

    // Metoda, która mówi Boostowi, co ma zapisać z tej klasy
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & clients;
    }
public:
    /**
     * @brief Konstruktor domyślny.
     * @details Inicjalizuje puste repozytorium klientów.
     */
    ClientRepository() = default;

    /**
     * @brief Destruktor klasy ClientRepository.
     * @details Zwalnia zasoby zarządzane przez repozytorium.
     */
    ~ClientRepository();

    /**
     * @brief Pobiera klienta o określonym indeksie.
     * @param index Pozycja w repozytorium.
     * @return ClientPtr Wskaźnik do klienta lub nullptr, jeśli indeks jest nieprawidłowy.
     */
    ClientPtr get(int index) const;


    /**
     * @brief Dodaje klienta do repozytorium.
     * @param client Wskaźnik do dodawanego obiektu. Pomija nullptr.
     */
    void add(ClientPtr client);

    /**
     * @brief Usuwa klienta z repozytorium.
     * @param client Wskaźnik do klienta, który ma zostać usunięty.
     */
    void remove(ClientPtr client);

    /**
     * @brief Generuje tekstowy raport o wszystkich klientach.
     * @return std::string Zbiorcze informacje o obiektach w repozytorium.
     */
    std::string report() const;

    /**
     * @brief Zwraca aktualną liczbę klientów.
     * @return int Rozmiar kolekcji.
     */
    int size() const;

    /**
     * @brief Metoda wyszukująca obiekty spełniające podane kryterium (predykat).
     * @param predicate Funkcja lub lambda definiująca warunek wyszukiwania.
     * @return std::vector<ClientPtr> Wektor wskaźników do znalezionych klientów.
     */
    std::vector<ClientPtr> findBy(ClientPredicate predicate) const;

    /**
     * @brief Zwraca wszystkich klientów znajdujących się w repozytorium.
     * @return std::vector<ClientPtr> Wektor wszystkich obiektów.
     */
    std::vector<ClientPtr> findAll() const;

    /**
     * @brief Wyszukuje klienta na podstawie unikalnego numeru PESEL.
     * @param personalId Ciąg znaków reprezentujący PESEL.
     * @return ClientPtr Wskaźnik do znalezionego klienta lub nullptr, jeśli nie istnieje.
     * @note Metoda jest wrażliwa na dokładne dopasowanie ciągu znaków.
     */
    ClientPtr findByPersonalId(const std::string& personalId) const;
};


#endif //PROJECTPOBI_CLIENTREPOSITORY_H