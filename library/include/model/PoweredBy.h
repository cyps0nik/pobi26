#ifndef CARRENTAL_POWEREDBY_H
#define CARRENTAL_POWEREDBY_H

#include <boost/serialization/access.hpp>
#include <string>
class PoweredBy {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Puste w środku, bo nie ma tu żadnych zmiennych do zapisu,
        // ale TA metoda musi istnieć!
    }
public:
    virtual ~PoweredBy() = default;
    virtual double getMultiplier() const = 0;
    virtual std::string getInfo() const = 0;
};


#endif //CARRENTAL_POWEREDBY_H