/**
 * @file ClientRepository.cpp
 * @brief Implementacja metod klasy ClientRepository.
 * @details Implementacja wykorzystuje standardowy kontener std::vector do przechowywania
 * inteligentnych wskaźników oraz algorytmy biblioteki standardowej (std::remove) do
 * efektywnego zarządzania kolekcją.
 */

#include "repositories/ClientRepository.h"
#include "model/Client.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

ClientRepository::~ClientRepository() {}

ClientPtr ClientRepository::get(int index) const {
    if (index < 0 || index >= (int)clients.size()) return nullptr;
    return clients[index];
}

void ClientRepository::add(ClientPtr client) {
    if (client != nullptr) {
        clients.push_back(client);
    }
}

void ClientRepository::remove(ClientPtr client) {
    if (client != nullptr) {
        clients.erase(
            std::remove(clients.begin(), clients.end(), client),
            clients.end()
        );
    }
}

std::string ClientRepository::report() const {
    std::stringstream ss; // Bufor obiektu string

    for (ClientPtr client : clients) {
        if (client != nullptr) {
            // Dodajemy info o kliencie do bufora
            ss << client->getInfo() << "\n";
        }
    }
    // Zamieniamy zawartość bufora na jeden obiekt typu string
    return ss.str();
}

int ClientRepository::size() const {
    return (int)clients.size();
}

std::vector<ClientPtr> ClientRepository::findBy(ClientPredicate predicate) const {
    std::vector<ClientPtr> found;
    for (unsigned int i = 0; i < clients.size(); i++) {
        ClientPtr client = get(i);
        if (client != nullptr && predicate(client)) {
            found.push_back(client);
        }
    }
    return found;
}

std::vector<ClientPtr> ClientRepository::findAll() const {
    return findBy([](const ClientPtr& /*client*/) { return true; });
}

ClientPtr ClientRepository::findByPersonalId(const std::string& personalId) const {
    ClientPredicate predicate = [personalId](const ClientPtr& c) {
        return c != nullptr && c->getPersonalID() == personalId;
    };

    std::vector<ClientPtr> found = findBy(predicate);
    if (found.empty()) {
        return nullptr;
    }
    else{
        return found[0];
    }
}