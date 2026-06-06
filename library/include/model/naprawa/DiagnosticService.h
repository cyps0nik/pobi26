#ifndef WARSZTATSAMOCHDOWY_DIAGNOSTICSERVICE_H
#define WARSZTATSAMOCHDOWY_DIAGNOSTICSERVICE_H
#include "Service.h"
class DiagnosticService : public Service{
private:
int fixedPrice;
public:
    DiagnosticService(const std::string& _name, const int& _price);
    int getServiceCost() const override;
    std::string getInfo() const override;
};


#endif //WARSZTATSAMOCHDOWY_DIAGNOSTICSERVICE_H