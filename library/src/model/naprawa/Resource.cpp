#include "model/naprawa/Resource.h"
Resource::Resource(const std::string &name, const ResourceType &res) : resourceName(name), resourceTyp(res), isBusy(false) {}
const std::string &Resource::getResourceName() const {
    return this->resourceName;
}
const ResourceType &Resource::getResourceType() const {
    return this->resourceTyp;
}
bool Resource::isAvailable() const {
    if (this->isBusy) return false;
    else return true;
}
std::string Resource::getInfo() const {
    std::string enumik, boolson;
    switch (resourceTyp) {
        case ResourceType::carLift: enumik = "podnosnik";
            break;
        case ResourceType::diagnosticComputer: enumik = "komputer diagnostyczny";
            break;
        case ResourceType::airCompressor: enumik = "kompresor";
            break;
        default: enumik = "narzedzie";
    }
    if (isAvailable()) boolson = "dostpene";
    else boolson = "niedostepne";
    return "Zasob, rodzaj zasobu: " + enumik + ", nazwa tego zasobu: " + getResourceName() + ", dostepnosc: " + boolson;
}



