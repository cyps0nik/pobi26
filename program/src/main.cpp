#include <iostream>
#include <model/Engine.h>

#include "DataSeeder.h"
#include "LogicContainer.h"
#include "StorageContainer.h"
#include "UserInterface.h"
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

    LogicContainer appa;
    LogicContainer tests;

    DataSeeder::prepareSystem(*appa.getStorage(), "warsztat_data.txt");
    DataSeeder::prepareSystem(*tests.getStorage(), "tests_data.txt");

    cout << "System gotowy do pracy!" << endl;

    std::remove("tests_data.txt");

    /* <------------------------- PROGRAM -------------------------> */
    LogicContainerPtr appLogic = make_shared<LogicContainer>();
    DataSeeder::prepareSystem(*appLogic->getStorage(), "warsztat_data.txt");

    UserInterface ui(appLogic);
    ui.run();



    return 0;
}