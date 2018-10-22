#ifndef PROJECT_SWA_GRAVITYSYSTEM_H
#define PROJECT_SWA_GRAVITYSYSTEM_H

#include "IBaseSystem.h"

class GravitySystem : public IBaseSystem {
private:
    std::shared_ptr<EntityManager> _entityManager;
public:
    GravitySystem(std::shared_ptr<EntityManager> entityManager);
    ~GravitySystem() override;
    void update(double dt) override;
};

#endif //PROJECT_SWA_GRAVITYSYSTEM_H
