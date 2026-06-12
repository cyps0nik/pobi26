#ifndef WARSZTATSAMOCHDOWY_DIAGNOSTICSERVICE_H
#define WARSZTATSAMOCHDOWY_DIAGNOSTICSERVICE_H
#include "Service.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class DiagnosticService : public Service {
private:
    int fixedPrice;

    // Dodajemy uprawnienia BOOSTOWI
    DiagnosticService() = default;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // 1. Najpierw serializujemy klasę bazową
        ar & boost::serialization::base_object<Service>(*this);

        // 2. Potem zmienne z tej konkretnej klasy
        ar & fixedPrice;
    }

public:
    DiagnosticService(const std::string &_name, const int &_price, const ResourceAbstractionPtr &_resource,
                      const MechanicAbstractionPtr &_mechanic);

    double getServiceCost() const override;

    std::string getInfo() const override;
};


#endif //WARSZTATSAMOCHDOWY_DIAGNOSTICSERVICE_H
