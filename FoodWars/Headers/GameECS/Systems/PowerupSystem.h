#ifndef PROJECT_SWA_POWERUPMANAGER_H
#define PROJECT_SWA_POWERUPMANAGER_H

#include <cstdlib>
#include "../Entities/EntityManager.h"
#include "../Events/CollisionEventHandler.h"
#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/General/Random.h"

class PowerupSystem :  public IBaseSystem, public CollisionEventHandler {
private:
    EntityManager *_entityManager;
public:
    PowerupSystem(IObservable<CollisionEvent> &collisionEventObservable, EntityManager &entityManager);
    ~PowerupSystem() = default;

    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override;
    void spawnPowerup();
    void update(double deltaTime) override;
};

#endif //PROJECT_SWA_POWERUPMANAGER_H
