/**
 * @file LogicContainer.cpp
 * @brief Implementacja kontenera logiki i inicjalizacja managerów.
 * @details Plik definiuje sposób powiązania managerów z repozytoriami oraz
 * wprowadza dodatkowe dane testowe specyficzne dla testów funkcjonalnych.
 */

#include "../include/LogicContainer.h"
#include "../include/StorageContainer.h"
#include "managers/CarManager.h"
#include "managers/ClientManager.h"
#include "managers/MechanicManager.h"
#include "managers/RepairManager.h"
#include "managers/ResourceManager.h"

using namespace std;

LogicContainer::LogicContainer() {
    // Najpierw tworzymy magazyn z pewnymi gotoqwymi danymi
    storage = std::make_shared<StorageContainer>();

    // Inicjalizujemy zarządców
    clientManager = std::make_shared<ClientManager>(storage->getClientRepository());
    carManager = std::make_shared<CarManager>(storage->getCarRepository());
    mechanicManager = std::make_shared<MechanicManager>(storage->getMechanicRepository());
    resourceManager = std::make_shared<ResourceManager>(storage->getResourceRepository());
    repairManager = std::make_shared<RepairManager>(storage->getRepairRepository());
}

LogicContainer::~LogicContainer() {}

// Gettery -> pozwalają UI (lub main) dostać się do odpowiedniego menedżera
ClientManagerPtr LogicContainer::getClientManager() const { return clientManager; }
CarManagerPtr LogicContainer::getCarManager() const { return carManager; }
MechanicManagerPtr LogicContainer::getMechanicManager() const { return mechanicManager; }
RepairManagerPtr LogicContainer::getRepairManager() const { return repairManager; }
ResourceManagerPtr LogicContainer::getResourceManager() const { return resourceManager; }

// Metoda zapisywania stanu systemu
void LogicContainer::saveSystem(const std::string& filename) const {
    if (storage) { // Sprawdź, czy wskaźnik nie jest nullptr
        storage->saveToFile(filename);
    } else {
        std::cerr << "Błąd: Brak zainicjalizowanego magazynu danych (storage)!" << std::endl;
    }
}
