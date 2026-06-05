/**
 * @file ResourceManager.cpp
 * @brief Implementacja logiki zarządzania zasobami.
 * @details Zawiera definicje metod odpowiedzialnych za rejestrację nowych zasobów,
 * ich wyszukiwanie w repozytorium oraz bezpieczne wyrejestrowywanie (archiwizację).
 */

#include "../../include/managers/ResourceManager.h"
#include "repositories/ResourceRepository.h"
#include "model/Resource.h"

using namespace std;

ResourceManager::ResourceManager(ResourceRepository& repo) : resourceRepository(repo) {}

// ResourcePtr ResourceManager::getResource(int id) const {
//     //
// }

