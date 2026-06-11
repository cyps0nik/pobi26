/**
 * @file MechanicManager.cpp
 * @brief Implementacja logiki zarządzania mechanikami.
 * @details Zawiera definicje metod odpowiedzialnych za rejestrację nowych mechaników,
 * ich wyszukiwanie w repozytorium oraz bezpieczne wyrejestrowywanie (archiwizację).
 */

#include "../../include/managers/MechanicManager.h"
#include "repositories/MechanicRepository.h"
#include "model/naprawa/Mechanic.h"

using namespace std;

MechanicManager::MechanicManager(MechanicRepository& repo) : mechanicRepository(repo) {}

MechanicPtr MechanicManager::getMechanic(int id) const {
    // Bezpośrednia delegacja odpowiedzialności do repozytorium
    return mechanicRepository.findById(id);
}

MechanicPtr MechanicManager::registerMechanic(const std::string& firstName, const std::string& lastName, const Specialization &spec) {
    // 1. Dynamicznie szukamy pierwszego wolnego ID mechanika
    while (getMechanic((int)nextId) != nullptr) {
        nextId++;
    }

    // 2. Tworzymy nowego mechanika i od razu inkrementujemy licznik
    MechanicPtr newMechanic = make_shared<Mechanic>(nextId++, firstName, lastName, spec);
    // 3. Dodajemy do repozytorium
    mechanicRepository.add(newMechanic);
    return newMechanic;
}

void MechanicManager::unregisterMechanic(MechanicPtr mechanic) {
    if (mechanic != nullptr) {
        // Sprawdzamy, czy mechanik jest w repozytorium
        MechanicPtr found = getMechanic(mechanic->getId());
        if (found != nullptr) {
            found->setBusy(true);
        }
    }
}

std::vector<MechanicPtr> MechanicManager::findMechanics(MechanicPredicate predicate) const {
    return mechanicRepository.findBy([predicate](const MechanicPtr& m) {
        return m != nullptr && predicate(m);
    });
}

std::vector<MechanicPtr> MechanicManager::findAllMechanics() const {
    return findMechanics([](const MechanicPtr&) { return true; });
}

std::vector<MechanicPtr> MechanicManager::findAvailableMechanics() const {
    return findMechanics([](const MechanicPtr& m) { return !m->isAvailable(); });
}

