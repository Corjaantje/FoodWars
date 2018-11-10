#ifndef PROJECT_SWA_GRAVITYSYSTEM_H
#define PROJECT_SWA_GRAVITYSYSTEM_H

#include "IBaseSystem.h"
#include "../Events/CollisionEventHandler.h"

class GravitySystem : public IBaseSystem, public CollisionEventHandler {
private:
    std::shared_ptr<EntityManager> _entityManager;
public:
    GravitySystem(std::shared_ptr<EntityManager> entityManager, IObservable<CollisionEvent>& collisionEventObservable);
    ~GravitySystem() override;
    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override;
    void update(double dt) override;
};

#endif //PROJECT_SWA_GRAVITYSYSTEM_H
