/**
 * @file ResourceManager.cpp
 * @brief Implementacja logiki zarządzania zasobami.
 * @details Zawiera definicje metod odpowiedzialnych za rejestrację nowych zasobów,
 * ich wyszukiwanie w repozytorium oraz bezpieczne wyrejestrowywanie (archiwizację).
 */

#include "../../include/managers/ResourceManager.h"
#include "repositories/ResourceRepository.h"
#include "model/naprawa/Resource.h"
#include "model/naprawa/ResourceAbstraction.h"

using namespace std;
namespace pt = boost::posix_time;

ResourceManager::ResourceManager(ResourceRepository& repo) : resourceRepository(repo) {}

ResourcePtr ResourceManager::getResource(int id) const {
    // Bezpośrednia delegacja odpowiedzialności do repozytorium
    return resourceRepository.findById(id);
}

ResourcePtr ResourceManager::registerResource(const std::string& resourceName, const ResourceType &res) {
    // 1. Dynamicznie szukamy pierwszego wolnego ID zasobu
    while (getResource((int)nextId) != nullptr) {
        nextId++;
    }

    // 2. Tworzymy nowy zasób i od razu inkrementujemy licznik
    ResourcePtr newResource = make_shared<Resource>(nextId++, resourceName, res);

    // 3. Dodajemy do repozytorium
    resourceRepository.add(newResource);

    return newResource;
}

void ResourceManager::unregisterResource(ResourcePtr resource) {
    if (resource != nullptr) {
        // Sprawdzamy, czy klient jest w repozytorium
        ResourcePtr found = getResource(resource->getId());
        if (found != nullptr) {
            found->setBusy(true);
        }
    }
}

vector<ResourcePtr> ResourceManager::findResources(ResourcePredicate predicate) const {
    return resourceRepository.findBy([predicate](const ResourcePtr& r) {
        return r != nullptr && predicate(r) && r->isAvailable();
    });
}

vector<ResourcePtr> ResourceManager::findAllResources() const {
    return findResources([](const ResourcePtr&) { return true; });
}