//
// Created by cypri on 1.06.2026.
//

#ifndef WARSZTATSAMOCHDOWY_SERVICE_H
#define WARSZTATSAMOCHDOWY_SERVICE_H
#include <string>
#include "typedefs.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>

class Service {
    private:
    std::string name;
    bool repaired;
    ResourceAbstractionPtr assignedResource;
    MechanicAbstractionPtr assignedMechanic;

    // Dodajemy uprawnienia BOOSTOWI
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & name;
        ar & repaired;
        ar & assignedResource;
        ar & assignedMechanic;
    }
public:
    Service(const std::string &_name, const ResourceAbstractionPtr& _resource, const MechanicAbstractionPtr& _mechanic);

    virtual ~Service() = default;

    const std::string &getName() const;

    const bool &isRepaired() const;

    const ResourceAbstractionPtr &getAssignedResource() const;

    const MechanicAbstractionPtr &getAssignedMechanic() const;

    virtual double getServiceCost() const = 0;

    virtual std::string getInfo() const;


};


#endif //WARSZTATSAMOCHDOWY_SERVICE_H
