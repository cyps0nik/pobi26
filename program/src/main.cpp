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
    //ClientPtr testClient = make_shared<Client>("Test", "Testowy", "111222333", "test@mail.com", "00000000000");
    //storage.getClientRepository().add(testClient);


    // 4. Usuwamy klienta
    ClientPtr c = storage.getClientRepository().get(2);
    storage.getClientRepository().remove(c);

    int rozmiarPo = storage.getClientRepository().size();
    cout << "Liczba klientow po odjęciu: " << rozmiarPo << endl;

    // 5. Wymuszamy zapis całego warsztatu do pliku
    storage.saveToFile("warsztat_data.txt");

    //std::remove("warsztat_data.txt");

    return 0;
}