#ifndef WARSZTATSAMOCHODOWY_RESOURCEABSTRACTION_H
#define WARSZTATSAMOCHODOWY_RESOURCEABSTRACTION_H

#include <boost/serialization/access.hpp>

class ResourceAbstraction {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Puste w środku, bo nie ma tu żadnych zmiennych do zapisu,
        // ale TA metoda musi istnieć!
    }
public:
};


#endif //WARSZTATSAMOCHODOWY_RESOURCEABSTRACTION_H