#include <iostream>
#include <model/Engine.h>
#include "StorageContainer.h"
#include "model/Client.h"
#include "model/Car.h"
#include "model/naprawa/Repair.h"
using namespace std;

int main() {
    Engine silnik(8000, Diesel);
    cout << silnik.getFuelType() << endl << "działa:D";
    cout << endl << "Siema" << endl;

    cout << "--- TEST ZAPISU I ODCZYTU ---" << endl;

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
    ClientPtr c = storage.getClientRepository().get(2);
    storage.getClientRepository().remove(c);

    int rozmiarPoPo = storage.getClientRepository().size();
    cout << "Liczba klientow po odjęciu: " << rozmiarPoPo << endl;

    // 5. Wymuszamy zapis całego projektu do pliku
    storage.saveToFile("project_data.txt");

    //Usuanie zawartości pliku "project_data.txt"
    //std::remove("project_data.txt");

    return 0;
}