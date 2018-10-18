#ifndef PROJECT_SWA_BASESYSTEMS_H
#define PROJECT_SWA_BASESYSTEMS_H

#include "../Entities/EntityManager.h"

class IBaseSystem {
public:
    IBaseSystem() = default;
    virtual ~IBaseSystem(){};
    virtual void update(double dt) = 0;
};


#endif //PROJECT_SWA_BASESYSTEMS_H
