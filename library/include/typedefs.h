#ifndef CARRENTAL_TYPEDEFS_H
#define CARRENTAL_TYPEDEFS_H
#include <memory>
class Car; class Client; class PoweredBy; class Service;
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Car> CarPtr;
typedef std::shared_ptr<Service> ServicePtr;
typedef std::unique_ptr<PoweredBy> PoweredUniqPtr;
#endif //CARRENTAL_TYPEDEFS_H