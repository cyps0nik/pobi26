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
    Service(const std::string &_name);

    virtual ~Service() = default;

    const std::string &getName() const;

    const bool &isRepaired() const;

    virtual double getServiceCost() const = 0;

    virtual std::string getInfo() const;
};


#endif //WARSZTATSAMOCHDOWY_SERVICE_H
