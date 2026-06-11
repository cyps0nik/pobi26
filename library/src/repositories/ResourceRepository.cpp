/**
 * @file ResourceRepository.cpp
 * @brief Implementacja metod zarządzania zasobami.
 */

#include "repositories/ResourceRepository.h"
#include "model/naprawa/Resource.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;


ResourcePtr ResourceRepository::get(int index) const {
    if (index < 0 || index >= (int)resources.size()) return nullptr;
    return resources[index];
}

void ResourceRepository::add(ResourcePtr resource) {
    if (resource != nullptr) resources.push_back(resource);
}

void ResourceRepository::remove(ResourcePtr resource) {
    if (resource != nullptr) {
        resources.erase(std::remove(resources.begin(), resources.end(), resource), resources.end());
    }
}

std::string ResourceRepository::report() const {
    std::stringstream ss;
    for (ResourcePtr resource : resources) {
        if (resource != nullptr) ss << resource->getInfo() << "\n";
    }
    return ss.str();
}

int ResourceRepository::size() const {
    return (int)resources.size();
}

std::vector<ResourcePtr> ResourceRepository::findBy(ResourcePredicate predicate) const {
    std::vector<ResourcePtr> found;
    for (ResourcePtr resource : resources) {
        if (resource != nullptr && predicate(resource)) {
            found.push_back(resource);
        }
    }
    return found;
}

std::vector<ResourcePtr> ResourceRepository::findAll() const {
    return findBy([](const ResourcePtr&) { return true; });
}

ResourcePtr ResourceRepository::findById(int id) const {
    ResourcePredicate predicate = [id](const ResourcePtr& r) {
        return r != nullptr && r->getId() == id;
    };

    std::vector<ResourcePtr> found = findBy(predicate);
    if (found.empty()) {
        return nullptr;
    }
    else{
        return found[0];
    }
}