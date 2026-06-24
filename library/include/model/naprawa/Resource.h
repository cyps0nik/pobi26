#ifndef WARSZTATSAMOCHODOWY_RESOURCE_H
#define WARSZTATSAMOCHODOWY_RESOURCE_H
#include "ResourceAbstraction.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>

enum ResourceType {
    carLift = 10, diagnosticComputer = 20, airCompressor = 30, tools = 40
};

class Resource : public ResourceAbstraction {
private:
    int id;
    std::string resourceName;
    ResourceType resourceTyp;
    bool isBusy;

    // Dodajemy uprawnienia BOOSTOWI
    Resource() = default;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<ResourceAbstraction>(*this);
        ar & id;
        ar & resourceName;
        ar & resourceTyp;
        ar & isBusy;
    }
public:
    Resource(const int& ident, const std::string &name, const ResourceType &res);

    const int& getId() const;

    const std::string &getResourceName() const;

    const ResourceType &getResourceType() const;

    const bool &getBusy() const override;

    void setBusy(const bool &zmiana) override;

    bool isAvailable() const override;

    std::string getInfo() const override;
};


#endif //WARSZTATSAMOCHODOWY_RESOURCE_H
