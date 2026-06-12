/**
* @file DataSeeder.h
 * @brief Klasa pomocnicza odpowiedzialna za wypełnianie magazynu danych obiektami testowymi.
 * @details Zgodnie z zasadą Single Responsibility Principle, klasa ta jest jedynym miejscem,
 * w którym znajduje się logika tworzenia danych początkowych (seedowania).
 */

#ifndef WARSZTATSAMOCHODOWY_DATASEEDER_H
#define WARSZTATSAMOCHODOWY_DATASEEDER_H
#include "StorageContainer.h"

/**
 * @class DataSeeder
 * @brief Klasa narzędziowa do wstrzykiwania przykładowych danych do systemu.
 */
class DataSeeder {
public:
 /**
  * @brief Główna metoda przygotowująca system do pracy.
  * @details Jeśli plik istnieje, ładuje dane; jeśli nie, wykonuje pełne "sianie"
  * i zapisuje wynik do pliku, aby przy kolejnym starcie było szybciej.
  * @param storage Referencja do kontenera z danymi.
  * @param filename Ścieżka do pliku z danymi.
  */
 static void prepareSystem(StorageContainer& storage, const std::string& filename);

 /**
  * @brief Wypełnia wskazany kontener danych podstawowym zestawem obiektów (klienci, auta, naprawy).
  * @details Metoda ta tworzy instancje obiektów biznesowych i dodaje je bezpośrednio do repozytoriów.
  * @param storage Referencja do kontenera StorageContainer, który ma zostać wypełniony.
  */
 static void seed(StorageContainer& storage);
};


#endif //WARSZTATSAMOCHODOWY_DATASEEDER_H