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