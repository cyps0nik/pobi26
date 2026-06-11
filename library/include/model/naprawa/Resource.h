#ifndef WARSZTATSAMOCHODOWY_RESOURCE_H
#define WARSZTATSAMOCHODOWY_RESOURCE_H
#include "ResourceAbstraction.h"
#include <string>

enum ResourceType {
    carLift = 10, diagnosticComputer = 20, airCompressor = 30, tools = 40
};

class Resource : public ResourceAbstraction {
private:
    int id;
    std::string resourceName;
    ResourceType resourceTyp;
    bool isBusy;

public:
    Resource(const int& ident, const std::string &name, const ResourceType &res);

    const int& getId() const;

    const std::string &getResourceName() const;

    const ResourceType &getResourceType() const;

    const bool &getBusy() const;

    void setBusy(const bool &zmiana);

    bool isAvailable() const;

    std::string getInfo() const;
};


#endif //WARSZTATSAMOCHODOWY_RESOURCE_H
