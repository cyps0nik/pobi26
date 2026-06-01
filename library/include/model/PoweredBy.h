#ifndef CARRENTAL_POWEREDBY_H
#define CARRENTAL_POWEREDBY_H


class PoweredBy {
private:

public:
    virtual ~PoweredBy() = default;
    virtual double getMultiplier() const = 0;
};


#endif //CARRENTAL_POWEREDBY_H