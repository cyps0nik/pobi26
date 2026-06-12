/**
 * @file StorageContainer.cpp
 * @brief Implementacja magazynu danych i mechanizmu "seeding".
 * @details Plik zawiera definicję konstruktora, który tworzy bazowe obiekty (Client, Car, Mechanic, Repair, Resource)
 * i umieszcza je w repozytoriach, zapewniając dane startowe do testowania aplikacji warsztatu.
 */

#include "StorageContainer.h"
#include "model/Client.h"
#include "model/Car.h"
#include "model/PoweredBy.h"
#include "model/naprawa/Mechanic.h"
#include "model/naprawa/Repair.h"
#include "model/naprawa/Resource.h"

#include <boost/date_time.hpp>

#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace pt = boost::posix_time;

using namespace std;

StorageContainer::StorageContainer() {
    std::string defaultFilename = "warsztat_data.txt";
    std::ifstream checkFile(defaultFilename);

    if (checkFile.is_open()) {
        // Jeśli plik istnieje, zamykamy go i wczytujemy dane za pomocą naszej metody
        checkFile.close();
        loadFromFile(defaultFilename);
    } else{
        // Jeśli pliku NIE MA, ładujemy dane testowe
        cout << "Brak pliku z danymi. Tworzenie danych testowych..." << endl;

        // DODAWANIE DANYCH TESTOWYCH

        // 1. Dodawanie Klientów
        // firstName, lastName, phoneNumber, email, PersonalID
        ClientPtr c1 = std::make_shared<Client>("Jan", "Kowalski", "123456789", "jan.kowalski@mail.com", "90010112345");
        ClientPtr c2 = std::make_shared<Client>("Anna", "Nowak", "987654321", "anna.nowak@mail.com", "92020254321");
        ClientPtr c3 = std::make_shared<Client>("Brajanusz", "Usłyszalski", "746523190", "brajanek.uszylal@mail.com", "09283019203");

        clientRepository.add(c1);
        clientRepository.add(c2);
        clientRepository.add(c3);

        // 2. Dodawanie Samochodów
        // carBrand, carModel, VIN
        CarPtr car1 = std::make_shared<Car>("Toyota", "Yaris", "VIN111111111", nullptr, c1);
        CarPtr car2 = std::make_shared<Car>("Honda", "Civic", "VIN222222222", nullptr, c2);

        carRepository.add(car1);
        carRepository.add(car2);

        // 3. Dodawanie Mechaników
        // id, firstName, lastName, specializations

        Specialization sp2 = Electrician;
        Specialization sp5 = Master;
        MechanicPtr m1 = std::make_shared<Mechanic>(1, "Marek", "Klucz", sp2);
        MechanicPtr m2 = std::make_shared<Mechanic>(2, "Zdzislaw", "Srubka", sp5);

        mechanicRepository.add(m1);
        mechanicRepository.add(m2);

        // 4. Dodawanie Zasobów
        // resourceName, resourceType

        ResourceType t1 = carLift;
        ResourceType t2 = diagnosticComputer;
        ResourcePtr res1 = std::make_shared<Resource>(1, "Stanowisko z podnosnikiem nr 1", t1);
        ResourcePtr res2 = std::make_shared<Resource>(2, "Skaner diagnostyczny OBD-II", t2);

        resourceRepository.add(res1);
        resourceRepository.add(res2);

        // 5. Dodawanie Napraw
        // id, beginTime, car
        RepairPtr rep1 = std::make_shared<Repair>(1, pt::second_clock::local_time(), car1);

        repairRepository.add(rep1);

        // NA KONIEC ZAPISUJEMY TE DANE TOSTOWE DO PLIKU:
        saveToFile(defaultFilename);
    }
}

// GETTERY DO REPÓW

ClientRepository& StorageContainer::getClientRepository() { 
    return clientRepository; 
}

CarRepository& StorageContainer::getCarRepository() { 
    return carRepository; 
}

MechanicRepository& StorageContainer::getMechanicRepository() { 
    return mechanicRepository; 
}

RepairRepository& StorageContainer::getRepairRepository() { 
    return repairRepository; 
}

ResourceRepository& StorageContainer::getResourceRepository() { 
    return resourceRepository; 
}


/*     <-----Ładowanie i zczytywanie z/do pliku----->     */


void StorageContainer::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        boost::archive::text_oarchive oa(ofs);
        // Zapisujemy cały kontener, co automatycznie zapisze wszystkie repozytoria
        oa & *this;
        std::cout << "Pomyślnie zapisano stan danych do pliku: " << filename << std::endl;
    } else {
        std::cerr << "Błąd: Nie udało się otworzyć pliku do zapisu!" << std::endl;
    }
}

void StorageContainer::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
        boost::archive::text_iarchive ia(ifs);
        // Odtwarzamy cały kontener
        ia & *this;
        std::cout << "Pomyślnie wczytano stan danych z pliku: " << filename << std::endl;
    } else {
        std::cerr << "Błąd: Nie udało się otworzyć pliku do odczytu!" << std::endl;
    }
}