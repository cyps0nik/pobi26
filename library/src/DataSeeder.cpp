/**
* @file DataSeeder.cpp
 * @brief Implementacja klasy DataSeeder.
 */

#include "DataSeeder.h"
#include "model/Client.h"
#include "model/Car.h"
#include "model/PoweredBy.h"
#include "model/naprawa/Mechanic.h"
#include "model/naprawa/Repair.h"
#include "model/naprawa/Resource.h"
#include <iostream>

void DataSeeder::prepareSystem(StorageContainer& storage, const std::string& filename) {
    std::ifstream file(filename);

    if (file.good()) {
        file.close();
        std::cout << "[DataSeeder] Znaleziono plik danych '" << filename << "'. Wczytywanie..." << std::endl;
        storage.loadFromFile(filename);
    } else {
        std::cout << "[DataSeeder] Plik '" << filename << "' nie istnieje. Inicjalizacja danymi testowymi..." << std::endl;
        seed(storage);

        // Zapisujemy od razu, żeby zaoszczędzić czas przy następnym uruchomieniu
        storage.saveToFile(filename);
    }
}

void DataSeeder::seed(StorageContainer& storage) {
    // Pobranie repozytoriów
    ClientRepository& clientRepo = storage.getClientRepository();
    CarRepository& carRepo = storage.getCarRepository();
    MechanicRepository& mechanicRepo = storage.getMechanicRepository();
    ResourceRepository& resourceRepo = storage.getResourceRepository();
    RepairRepository& repairRepo = storage.getRepairRepository();


    // DODAWANIE DANYCH TESTOWYCH

        // 1. Dodawanie Klientów
        // firstName, lastName, phoneNumber, email, PersonalID
        ClientPtr c1 = std::make_shared<Client>("Jan", "Kowalski", "123456789", "jan.kowalski@mail.com", "90010112345");
        ClientPtr c2 = std::make_shared<Client>("Anna", "Nowak", "987654321", "anna.nowak@mail.com", "92020254321");
        ClientPtr c3 = std::make_shared<Client>("Brajanusz", "Usłyszalski", "746523190", "brajanek.uszylal@mail.com", "09283019203");

        clientRepo.add(c1);
        clientRepo.add(c2);
        clientRepo.add(c3);

        // 2. Dodawanie Samochodów
        // carBrand, carModel, VIN, power, owner
        CarPtr car1 = std::make_shared<Car>("Toyota", "Yaris", "VIN111111111", nullptr, c1);
        CarPtr car2 = std::make_shared<Car>("Honda", "Civic", "VIN222222222", nullptr, c2);

        carRepo.add(car1);
        carRepo.add(car2);

        // 3. Dodawanie Mechaników
        // id, firstName, lastName, specializations

        Specialization sp2 = Electrician;
        Specialization sp5 = Master;
        MechanicPtr m1 = std::make_shared<Mechanic>(1, "Marek", "Klucz", sp2);
        MechanicPtr m2 = std::make_shared<Mechanic>(2, "Zdzislaw", "Srubka", sp5);

        mechanicRepo.add(m1);
        mechanicRepo.add(m2);

        // 4. Dodawanie Zasobów
        // resourceName, resourceType

        ResourceType t1 = carLift;
        ResourceType t2 = diagnosticComputer;
        ResourcePtr res1 = std::make_shared<Resource>(1, "Stanowisko z podnosnikiem nr 1", t1);
        ResourcePtr res2 = std::make_shared<Resource>(2, "Skaner diagnostyczny OBD-II", t2);

        resourceRepo.add(res1);
        resourceRepo.add(res2);

        // 5. Dodawanie Napraw
        // id, beginTime, car
        RepairPtr rep1 = std::make_shared<Repair>(1, pt::second_clock::local_time(), car1);

        repairRepo.add(rep1);

        // NA KONIEC ZAPISUJEMY TE DANE TOSTOWE DO PLIKU:
        //saveToFile(defaultFilename);


    std::cout << "[DataSeeder] Pomyślnie zasiano dane testowe." << std::endl;
}
