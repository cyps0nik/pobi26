//
// Created by cypri on 1.06.2026.
//

#ifndef WARSZTATSAMOCHDOWY_SERVICE_H
#define WARSZTATSAMOCHDOWY_SERVICE_H
#include <string>

class Service {
    std::string name;
    bool repaired;
public:
    Service(std::string _name);
};


#endif //WARSZTATSAMOCHDOWY_SERVICE_H