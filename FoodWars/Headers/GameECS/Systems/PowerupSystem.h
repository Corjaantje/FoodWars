#ifndef PROJECT_SWA_POWERUPMANAGER_H
#define PROJECT_SWA_POWERUPMANAGER_H

#include <cstdlib>
#include "../Entities/EntityManager.h"
#include "../Events/CollisionEventHandler.h"
#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/General/Random.h"
#include "Misc/ItemFactory.h"
#include "../Events/TurnSwitchedEventHandler.h"
#include "Misc/WeaponFactory.h"

class PowerupSystem :  public IBaseSystem, public CollisionEventHandler, public TurnSwitchedEventHandler {
private:
    EntityManager *_entityManager;
public:
    PowerupSystem(IObservable<CollisionEvent> &collisionEventObservable, IObservable<TurnSwitchedEvent> &turnSwitchedEventObservable, EntityManager &entityManager);
    ~PowerupSystem() = default;

    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override;
    void handleTurnSwitchedEvent(const TurnSwitchedEvent& turnSwitchedEvent) override;

    void update(double deltaTime) override;
private:
    ItemFactory _itemFactory;
    WeaponFactory _weaponFactory;
    std::unordered_map<int, std::string> _weaponMap;
    std::unordered_map<int, std::string> _itemMap;
    void spawnPowerup();
    void spawnWeapon();
};

#endif //PROJECT_SWA_POWERUPMANAGER_H
