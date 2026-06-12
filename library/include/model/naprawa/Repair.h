//
// Created by cypri on 1.06.2026.
//

#ifndef WARSZTATSAMOCHDOWY_REPAIR_H
#define WARSZTATSAMOCHDOWY_REPAIR_H
#include <boost/date_time.hpp>
#include <vector>
#include "typedefs.h"
#include "Service.h"
#include "model/naprawa/Repair.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp> // Niezbędne dla pt::ptime!

namespace pt = boost::posix_time;

class Repair : std::enable_shared_from_this<Repair> {
    int id;
    double repairCost;
    pt::ptime beginTime;
    pt::ptime endTime;
    std::vector<ServicePtr> services;
    CarPtr repairedCar;
    bool archive = false; /**< Flaga określająca, czy naprawa jest zarchiwizowana. */

    // Dodajemy uprawnienia BOOSTOWI
    Repair() = default;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & id;
        ar & repairCost;
        ar & beginTime;
        ar & endTime;
        ar & services;
        ar & repairedCar;
        ar & archive;
    }

public:
    Repair(const int &_id, const pt::ptime &_beginTime, const CarPtr &_car);

    const int &getId() const;

    const double& getRepairCost() const;

    const pt::ptime &getBeginTime() const;

    const pt::ptime &getEndTime() const;

    CarPtr getCar() const;

    int getServicesAmount() const;

    double getSingleServiceCost(const ServicePtr &service) const;

    double calculateTotal();

    void add(const ServicePtr &service);

    void remove(const ServicePtr &service);

    ServicePtr get(const ServicePtr &service);

    std::string getInfo() const;

    std::string getSingleServiceInfo(const ServicePtr& service) const;

    std::string getRepairedCarInfo() const;
    /**
     * @brief Zwraca informację o statusie archiwalnym naprawy.
     * @return true jeśli naprawa jest zarchiwizowana, false jeśli jest aktywna.
     */
    bool isArchive() const;

    /**
     * @brief Zmienia status archiwalny naprawy.
     * @param archive Nowy stan flagi (true dla archiwizacji).
     */
    void setArchive(bool archive);
};


#endif //WARSZTATSAMOCHDOWY_REPAIR_H
