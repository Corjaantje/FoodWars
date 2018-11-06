#ifndef PROJECT_SWA_DAMAGEABLESYSTEM_H
#define PROJECT_SWA_DAMAGEABLESYSTEM_H

#include "IBaseSystem.h"
#include "../Components/DamageableComponent.h"

class DamageableSystem : public IBaseSystem
{
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::map<int, std::shared_ptr<DamageableComponent>> _damageableComponents;

public:
    DamageableSystem(std::shared_ptr<EntityManager> entityManager);
    ~DamageableSystem() override;

    void update(double deltaTime) override;

};
#endif //PROJECT_SWA_DAMAGEABLESYSTEM_H
