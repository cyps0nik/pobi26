/**
 * @file RepairManager.cpp
 * @brief Implementacja logiki zarządzania naprawami.
 * @details Zawiera definicje metod odpowiedzialnych za rejestrację nowych napraw,
 * ich wyszukiwanie w repozytorium oraz bezpieczne wyrejestrowywanie (archiwizację).
 */

#include "../../include/managers/RepairManager.h"
#include "repositories/RepairRepository.h"
#include "model/naprawa/Repair.h"

using namespace std;
namespace pt = boost::posix_time;

RepairManager::RepairManager(RepairRepository& repo) : repairRepository(repo) {}

RepairPtr RepairManager::getRepair(int id) const {
    // Bezpośrednia delegacja odpowiedzialności do repozytorium
    return repairRepository.findById(id);
}

RepairPtr RepairManager::registerRepair(const pt::ptime& beginTime, const CarPtr& car) {
    // 1. Dynamicznie szukamy pierwszego wolnego ID naprawy
    while (getRepair(nextId) != nullptr) {
        nextId++;
    }

    // 2. Tworzymy nową naprawę i od razu inkrementujemy licznik
    RepairPtr newRepair = make_shared<Repair>(nextId++, beginTime, car);

    // 3. Dodajemy do repozytorium
    repairRepository.add(newRepair);

    return newRepair;
}

void RepairManager::unregisterRepair(RepairPtr repair) {
    if (repair != nullptr) {
        // Sprawdzamy, czy klient jest w repozytorium
        RepairPtr found = getRepair(repair->getId());
        if (found != nullptr) {
            found->setArchive(true);
        }
    }
}

vector<RepairPtr> RepairManager::findRepairs(RepairPredicate predicate) const {
    return repairRepository.findBy([predicate](const RepairPtr& r) {
        return r != nullptr && predicate(r) && !r->isArchive();
    });
}

vector<RepairPtr> RepairManager::findAllRepairs() const {
    return findRepairs([](const RepairPtr&) { return true; });
}

vector<RepairPtr> RepairManager::findCurrentRepairs() const {
    return findRepairs([](const RepairPtr& r) {
        return r->getEndTime() == pt::not_a_date_time && r->isArchive() == false;
    });
}
