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
    int getServiceCost() const;
    const std::string &getName() const;
    const bool &isRepaired() const;

};


#endif //WARSZTATSAMOCHDOWY_SERVICE_H