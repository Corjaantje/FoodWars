#ifndef PROJECT_SWA_POWERUPSYSTEM_H
#define PROJECT_SWA_POWERUPSYSTEM_H

#include "IBaseSystem.h"

class PowerupSystem : public IBaseSystem {
private:
    EntityManager *_entityManager;
public:
    explicit PowerupSystem(EntityManager &entityManager);
    ~PowerupSystem() override;
    void update(double dt) override;
};

#endif //PROJECT_SWA_POWERUPSYSTEM_H
