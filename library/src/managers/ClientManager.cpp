/**
 * @file ClientManager.cpp
 * @brief Implementacja logiki zarządzania klientami.
 * @details Zawiera definicje metod odpowiedzialnych za rejestrację nowych klientów,
 * ich wyszukiwanie w repozytorium oraz bezpieczne wyrejestrowywanie (archiwizację).
 */

#include "../../include/managers/ClientManager.h"
#include "repositories/ClientRepository.h"
#include "model/Client.h"

using namespace std;

ClientManager::ClientManager(ClientRepository& repository) : clientRepository(repository) {}

ClientPtr ClientManager::getClient(const std::string& personalId) const {
    // Delegacja odpowiedzialności do repozytorium
    return clientRepository.findByPersonalId(personalId);
}

ClientPtr ClientManager::registerClient(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber, const std::string& email
, const std::string& personalId) {
    // 1. Sprawdzamy czy klient już istnieje
    ClientPtr existing = getClient(personalId);
    if (existing != nullptr) {
        return existing; // Zwracamy istniejący obiekt
    }

    // 2. Jeśli nie istnieje, tworzymy nowy
    ClientPtr newClient = std::make_shared<Client>(firstName, lastName, phoneNumber, email, personalId);

    // 3. Dodajemy do repozytorium
    clientRepository.add(newClient);

    return newClient;
}

void ClientManager::unregisterClient(ClientPtr client) {
    if (client != nullptr) {
        // Sprawdzamy, czy klient jest w repozytorium
        ClientPtr found = getClient(client->getPersonalID());
        if (found != nullptr) {
            found->setArchive(true);
        }
    }
}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate predicate) const {
    // Tworzymy nowy predykat będący iloczynem logicznym (warunek predykatu + nie jest zarchiwizowany)
    ClientPredicate compositePredicate = [predicate](const ClientPtr& c) {
        if (c != nullptr) {
            // Iloczyn logiczny: spełnia warunki predykatu ORAZ isArchive() == false
            return predicate(c) && !c->isArchive();
        }
        return false;
    };

    return clientRepository.findBy(compositePredicate);
}

std::vector<ClientPtr> ClientManager::findAllClients() const {
    // findAllClients zwraca wszystkich niezarchiwizowanych + przekazujemy predykat, który dla każdego elementu zwraca true
    return findClients([](const ClientPtr&) { return true; });
}