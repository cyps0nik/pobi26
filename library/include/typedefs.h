#ifndef CARRENTAL_TYPEDEFS_H
#define CARRENTAL_TYPEDEFS_H
#include <memory>
#include <functional>
class Client;
class Car;
class Resource;
class Mechanic;
class Repair;
class Service;
class PoweredBy;
class MechanicAbstraction;
class ResourceAbstraction;
class ClientManager;
class CarManager;
class MechanicManager;
class RepairManager;
class ResourceManager;
class LogicContainer;
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Car> CarPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Mechanic> MechanicPtr;
typedef std::shared_ptr<Repair> RepairPtr;
typedef std::shared_ptr<Service> ServicePtr;
typedef std::unique_ptr<PoweredBy> PoweredUniqPtr;
typedef std::shared_ptr<MechanicAbstraction> MechanicAbstractionPtr;
typedef std::shared_ptr<ResourceAbstraction> ResourceAbstractionPtr;

// --- Definicje typów wskaźnikowych (Managers & Logic) ---

/** @brief Inteligentny wskaźnik do obiektu klasy ClientManager. */
typedef std::shared_ptr<ClientManager> ClientManagerPtr;

/** @brief Inteligentny wskaźnik do obiektu klasy CarManager. */
typedef std::shared_ptr<CarManager> CarManagerPtr;

/** @brief Inteligentny wskaźnik do obiektu klasy MechanicManager. */
typedef std::shared_ptr<MechanicManager> MechanicManagerPtr;

/** @brief Inteligentny wskaźnik do obiektu klasy RepairManager. */
typedef std::shared_ptr<RepairManager> RepairManagerPtr;

/** @brief Inteligentny wskaźnik do obiektu klasy ResourceManager. */
typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;

/** @brief Inteligentny wskaźnik do obiektu klasy LogicContainer. */
typedef std::shared_ptr<LogicContainer> LogicContainerPtr;

// --- Definicje typów predykatów (Funkcje filtrujące) ---

/**
 * @brief Typ funkcyjny predykatu dla obiektów klasy Client.
 * @details Wykorzystywany w ClientRepository do filtrowania klientów.
 */
typedef std::function<bool(const ClientPtr&)> ClientPredicate;

/**
 * @brief Typ funkcyjny predykatu dla obiektów klasy Car.
 * @details Wykorzystywany w CarRepository do filtrowania pojazdów.
 */
typedef std::function<bool(const CarPtr&)> CarPredicate;

/**
 * @brief Typ funkcyjny predykatu dla obiektów klasy Resource.
 * @details Wykorzystywany w ResourceRepository do filtrowania pojazdów.
 */
typedef std::function<bool(const ResourcePtr&)> ResourcePredicate;

/**
 * @brief Typ funkcyjny predykatu dla obiektów klasy Mechanic.
 * @details Wykorzystywany w MechanicRepository do filtrowania pojazdów.
 */
typedef std::function<bool(const MechanicPtr&)> MechanicPredicate;

/**
 * @brief Typ funkcyjny predykatu dla obiektów klasy Repair.
 * @details Wykorzystywany RepairRepository do filtrowania pojazdów.
 */
typedef std::function<bool(const RepairPtr&)> RepairPredicate;
#endif //CARRENTAL_TYPEDEFS_H