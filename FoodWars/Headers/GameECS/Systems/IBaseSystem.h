#ifndef PROJECT_SWA_BASESYSTEMS_H
#define PROJECT_SWA_BASESYSTEMS_H

#include "../Entities/EntityManager.h"

class IBaseSystem {
public:
    IBaseSystem(EntityManager* entityManager): _entityManager(entityManager){}
    ~IBaseSystem();

    virtual void Update(double dt);

public:
    EntityManager* _entityManager;
};


#endif //PROJECT_SWA_BASESYSTEMS_H
