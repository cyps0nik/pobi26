#ifndef WARSZTATSAMOCHODOWY_RESOURCE_H
#define WARSZTATSAMOCHODOWY_RESOURCE_H
#include "ResourceAbstraction.h"
#include <string>

enum ResourceType {
    carLift = 10, diagnosticComputer = 20, airCompressor = 30, tools = 40
};

class Resource : public ResourceAbstraction {
private:
    std::string resourceName;
    ResourceType resourceTyp;
    bool isBusy;

public:
    Resource(const std::string &name, const ResourceType &res);

    const std::string &getResourceName() const;

    const ResourceType &getResourceType() const;

    bool isAvailable() const;

    std::string getInfo() const;
};


#endif //WARSZTATSAMOCHODOWY_RESOURCE_H
