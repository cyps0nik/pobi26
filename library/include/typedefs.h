#ifndef CARRENTAL_TYPEDEFS_H
#define CARRENTAL_TYPEDEFS_H
#include <memory>

class Client;
class Car;
class Resource;
class Mechanic;
class Repair;
class Service;
class PoweredBy;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Car> CarPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Mechanic> MechanicPtr;
typedef std::shared_ptr<Repair> RepairPtr;
typedef std::shared_ptr<Service> ServicePtr;
typedef std::unique_ptr<PoweredBy> PoweredUniqPtr;

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