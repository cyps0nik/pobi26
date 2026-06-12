#include <iostream>
#include <model/Engine.h>

#include "DataSeeder.h"
#include "LogicContainer.h"
#include "StorageContainer.h"
#include "model/Client.h"
#include "model/Car.h"
#include "model/naprawa/Repair.h"
using namespace std;

int main() {
    Engine silnik(8000, Diesel);
    cout << silnik.getFuelType() << endl << "działa:D";
    cout << endl << "Siema" << endl;

    cout << endl << "--- TEST ZAPISU I ODCZYTU (dla StorageContainer) ---" << endl;

    // 1. Tworzymy kontener
    StorageContainer storage;

    // 2. Sprawdzamy, ilu klientów mamy aktualnie w bazie
    int rozmiarPrzed = storage.getClientRepository().size();
    cout << "Liczba klientow na starcie: " << rozmiarPrzed << endl;

    // 3. Dodajemy nowego klienta
    ClientPtr testClient = make_shared<Client>("Test", "Testowy", "111222333", "test@mail.com", "00000000000");
    storage.getClientRepository().add(testClient);
    int rozmiarPo = storage.getClientRepository().size();
    cout << "Liczba klientow po dodaniu: " << rozmiarPo << endl;

    // 4. Usuwamy klienta
    storage.getClientRepository().remove(testClient);
    int rozmiarPoPo = storage.getClientRepository().size();
    cout << "Liczba klientow po odjęciu: " << rozmiarPoPo << endl;

    // 5. Wymuszamy zapis całego projektu do pliku
    storage.saveToFile("project_data.txt");

    //Usuanie zawartości pliku "project_data.txt"
    //std::remove("project_data.txt");

    cout << endl << "--- TEST ZAPISU I ODCZYTU (dla LogicContainer) ---" << endl;

    // 1. Inicjalizacja kontenera logiki (tworzy pusty StorageContainer i Managerów)
    LogicContainer app;

    // 2. Wybór trybu pracy
    bool trybTestowy = true;

    if (trybTestowy) {
        cout << "[INFO] Uruchamianie w trybie testowym..." << endl;
        // Używamy naszego Seedera, aby wypełnić repozytoria
        DataSeeder::seed(*app.getStorage());
    } else {
        std::cout << "[INFO] Wczytywanie danych z pliku..." << std::endl;
        app.getStorage()->loadFromFile("warsztat_data.txt");
    }
    cout << "System gotowy do pracy!" << endl;


    return 0;
}