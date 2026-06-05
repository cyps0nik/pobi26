/**
 * @file MechanicRepository.cpp
 * @brief Implementacja metod zarządzania mechanikami.
 */

#include "repositories/MechanicRepository.h"
#include "model/Mechanic.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

MechanicRepository::~MechanicRepository() {}

MechanicPtr MechanicRepository::get(int index) const {
    if (index < 0 || index >= (int)mechanics.size()) return nullptr;
    return mechanics[index];
}

void MechanicRepository::add(MechanicPtr mechanic) {
    if (mechanic != nullptr) mechanics.push_back(mechanic);
}

void MechanicRepository::remove(MechanicPtr mechanic) {
    if (mechanic != nullptr) {
        mechanics.erase(std::remove(mechanics.begin(), mechanics.end(), mechanic), mechanics.end());
    }
}

std::string MechanicRepository::report() const {
    std::stringstream ss;
    for (MechanicPtr mechanic : mechanics) {
        if (mechanic != nullptr) ss << mechanic->getInfo() << "\n";
    }
    return ss.str();
}

int MechanicRepository::size() const {
    return (int)mechanics.size();
}

std::vector<MechanicPtr> MechanicRepository::findBy(MechanicPredicate predicate) const {
    std::vector<MechanicPtr> found;
    for (MechanicPtr mechanic : mechanics) {
        if (mechanic != nullptr && predicate(mechanic)) {
            found.push_back(mechanic);
        }
    }
    return found;
}

std::vector<MechanicPtr> MechanicRepository::findAll() const {
    return findBy([](const MechanicPtr&) { return true; });
}

MechanicPtr MechanicRepository::findById(int id) const {
    MechanicPredicate predicate = [id](const MechanicPtr& m) {
        return m != nullptr && m->getId() == id;
    };

    std::vector<MechanicPtr> found = findBy(predicate);
    if (found.empty()) {
        return nullptr;
    }
    else {
        return found[0];
    }
}