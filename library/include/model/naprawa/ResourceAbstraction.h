#ifndef WARSZTATSAMOCHODOWY_RESOURCEABSTRACTION_H
#define WARSZTATSAMOCHODOWY_RESOURCEABSTRACTION_H

#include <boost/serialization/access.hpp>
#include <string>
class ResourceAbstraction {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Puste w środku, bo nie ma tu żadnych zmiennych do zapisu,
        // ale TA metoda musi istnieć!
    }
public:
    virtual ~ResourceAbstraction() = default;
    virtual bool isAvailable() const = 0;
    virtual std::string getInfo() const = 0;
};


#endif //WARSZTATSAMOCHODOWY_RESOURCEABSTRACTION_H