/**
 * @file UserInterface.h
 * @brief Definicja klasy UserInterface odpowiadającej za interfejs tekstowy CLI aplikacji warsztatu.
 */

#ifndef WARSZTATSAMOCHDOWY_USERINTERFACE_H
#define WARSZTATSAMOCHDOWY_USERINTERFACE_H

#include "LogicContainer.h"
#include <string>
#include <memory>

/**
 * @class UserInterface
 * @brief Klasa obsługująca interakcję z pracownikiem biura obsługi za pomocą konsoli (CLI).
 * @details Realizuje pełną integrację z warstwą logiczną systemu poprzez delegowanie zadań
 * do dedykowanych managerów domeny biznesowej. Zapobiega powstawaniu monolitycznych struktur menu.
 */
class UserInterface {
private:
    LogicContainerPtr logic; /**< Wskaźnik na kontener logiki biznesowej agregujący managerów systemu */

    /**
     * @brief Metoda czyszcząca bufor strumienia wejściowego w przypadku wystąpienia błędów walidacji.
     */
    void clearInputBuffer() const;

    /**
     * @brief Pomocnicza metoda do bezpiecznego wczytywania liczb całkowitych z obsługą błędnych typów danych.
     * @param prompt Komunikat instruktażowy wyświetlany pracownikowi w konsoli.
     * @return Zwalidowana, poprawnie wprowadzona liczba całkowita.
     */
    int readInt(const std::string& prompt) const;

    /**
     * @brief Pomocnicza metoda do bezpiecznego wczytywania ciągów tekstowych.
     * @param prompt Komunikat instruktażowy wyświetlany pracownikowi w konsoli.
     * @return Wczytany od użytkownika ciąg znaków (obsługuje spacje).
     */
    std::string readString(const std::string& prompt) const;

    // --- PODMENU MODULOWE ---

    /**
     * @brief Obsługa podmenu zarządzania danymi klientów oraz ich pojazdów.
     * @details Integruje operacje ClientManager oraz CarManager pozwalając na pełne operacje rejestracji i archiwizacji.
     */
    void manageClientsAndCars();

    /**
     * @brief Obsługa podmenu zarządzania procesami napraw (zleceniami).
     * @details Obsługuje zakładanie zleceń, podgląd stanu finansowego oraz finalne rozliczanie naprawy.
     */
    void manageRepairs();

    /**
     * @brief Dedykowany moduł planowania i weryfikacji dostępności podzespołów usługi.
     * @details Implementuje kontrolę dostępności wolnych pracowników oraz maszyn przed dopisaniem nowej pozycji.
     * @param repair Inteligentny wskaźnik na modyfikowany obiekt zlecenia naprawy.
     */
    void manageServicesForRepair(RepairPtr repair);

    /**
     * @brief Obsługa podmenu zarządzania zasobami technicznymi i personelem warsztatu.
     * @details Implementuje zaawansowane filtry wyszukiwania mechaników według specjalizacji i zasobów sprzętowych.
     */
    void manageResourcesAndPersonnel();

public:
    /**
     * @brief Konstruktor inicjalizujący interfejs użytkownika.
     * @param logicContainer Współdzielony wskaźnik na LogicContainer dostarczający zależności managerskie.
     */
    UserInterface(LogicContainerPtr logicContainer);

    /**
     * @brief Główna metoda uruchamiająca nieskończoną pętlę sterowania aplikacją tekstową.
     */
    void run();
};

#endif // WARSZTATSAMOCHDOWY_USERINTERFACE_H