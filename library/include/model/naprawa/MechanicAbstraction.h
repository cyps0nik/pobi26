#ifndef WARSZTATSAMOCHODOWY_ABSTRACTMECHANIC_H
#define WARSZTATSAMOCHODOWY_ABSTRACTMECHANIC_H
#include "typedefs.h"
#include <boost/serialization/access.hpp>
#include <string>
class MechanicAbstraction {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Puste w środku, bo nie ma tu żadnych zmiennych do zapisu,
        // ale TA metoda musi istnieć!
    }
public:
    virtual ~MechanicAbstraction() = default;
    virtual bool isAvailable() const = 0;
    virtual std::string getInfo() const = 0;
    virtual const bool &getBusy() const = 0;

    virtual void setBusy(const bool &zmiana) = 0;
};


#endif //WARSZTATSAMOCHODOWY_ABSTRACTMECHANIC_H