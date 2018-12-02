#ifndef PROJECT_SWA_DAMAGEABLESYSTEM_H
#define PROJECT_SWA_DAMAGEABLESYSTEM_H

#include "IBaseSystem.h"
#include "../Components/DamageableComponent.h"
#include "../Events/CollisionEventHandler.h"

class DamageableSystem : public IBaseSystem, CollisionEventHandler {
private:
    EntityManager *_entityManager;
public:
    DamageableSystem(EntityManager &entityManager, IObservable<CollisionEvent> &collisionEventObservable);
    ~DamageableSystem() override;

    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override;
    void update(double deltaTime) override;

};

#endif //PROJECT_SWA_DAMAGEABLESYSTEM_H
