//
// Created by marek on 4.06.2026.
//

#include "repositories/RepairRepository.h"
#include "model/Repair.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

RepairRepository::~RepairRepository() {}

RepairPtr RepairRepository::get(int index) const {
    if (index < 0 || index >= (int)repairs.size()) return nullptr;
    return repairs[index];
}

void RepairRepository::add(RepairPtr repair) {
    if (repair != nullptr) repairs.push_back(repair);
}

void RepairRepository::remove(RepairPtr repair) {
    if (repair != nullptr) {
        repairs.erase(std::remove(repairs.begin(), repairs.end(), repair), repairs.end());
    }
}

std::string RepairRepository::report() const {
    std::stringstream ss;
    for (RepairPtr repair : repairs) {
        if (repair != nullptr) ss << "Repair ID: " << repair->getId() << "\n";
    }
    return ss.str();
}

int RepairRepository::size() const {
    return (int)repairs.size();
}

std::vector<RepairPtr> RepairRepository::findBy(RepairPredicate predicate) const {
    std::vector<RepairPtr> found;
    for (RepairPtr repair : repairs) {
        if (repair != nullptr && predicate(repair)) {
            found.push_back(repair);
        }
    }
    return found;
}

std::vector<RepairPtr> RepairRepository::findAll() const {
    return findBy([](const RepairPtr&) { return true; });
}

RepairPtr RepairRepository::findById(int id) const {
    RepairPredicate predicate = [id](const RepairPtr& r) {
        return r != nullptr && r->getId() == id;
    };

    std::vector<RepairPtr> found = findBy(predicate);
    if (found.empty()) {
        return nullptr;
    }
    else{
        return found[0];
    }
}