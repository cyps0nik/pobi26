#ifndef CARRENTAL_TYPEDEFS_H
#define CARRENTAL_TYPEDEFS_H
#include <memory>
class Car; class Client;
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Car> CarPtr;
#endif //CARRENTAL_TYPEDEFS_H