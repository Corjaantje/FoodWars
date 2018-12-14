#include "../../../Headers/GameECS/Systems/PowerupSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/StateMachine/Misc/Coordinate.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/ItemComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"

PowerupSystem::PowerupSystem(IObservable<CollisionEvent> &collisionEventObservable, IObservable<TurnSwitchedEvent> &turnSwitchedEventObservable, EntityManager &entityManager)
        : CollisionEventHandler(collisionEventObservable), TurnSwitchedEventHandler(turnSwitchedEventObservable), _entityManager{&entityManager}, _itemFactory{ItemFactory{}}{
    _itemMap[0] = "cake";
    _itemMap[1] = "painkiller";
    _weaponMap[0] = "carrot";
    _weaponMap[1] = "ham";
    _weaponMap[2] = "candycane";

}

void PowerupSystem::spawnDrop(const std::unordered_map<int, std::string> &dropMap) {
    Random random;

    int weaponX = random.between(0, 1571);
    int weaponY = 0;
    int weaponWidth = 29;
    int weaponHeight = 42;

    int weaponID = _entityManager->createEntity();
    int weaponChance = random.between(0, dropMap.size()-1);

    const std::string &name = dropMap.at(weaponChance);
    auto weaponType = _itemFactory.createItem(name);
    _entityManager->addComponentToEntity(weaponID, std::make_unique<ItemComponent>(weaponType));
    // TODO: better sprite for representing a weapon drop
    _entityManager->addComponentToEntity<DrawableComponent>(weaponID,
                                                            std::make_unique<ShapeSprite>(weaponWidth, weaponHeight, weaponX, weaponY,
                                                                                          name +
                                                                                          ".png"));
    _entityManager->addComponentToEntity<BoxCollider>(weaponID, weaponWidth, weaponHeight);
    _entityManager->addComponentToEntity<PositionComponent>(weaponID, weaponX, weaponY);
    _entityManager->addComponentToEntity<GravityComponent>(weaponID, 5);
}
bool PowerupSystem::canHandle(const CollisionEvent &collisionEvent) {
    int player = collisionEvent.getEntity();
    int item = collisionEvent.getOtherEntity();
    return _entityManager->getComponentFromEntity<PlayerComponent>(player) &&
           _entityManager->getComponentFromEntity<ItemComponent>(item);
}

void PowerupSystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    int item = collisionEvent.getOtherEntity();
    auto itemComponent = _entityManager->getComponentFromEntity<ItemComponent>(item);
    if(!itemComponent) {
        item = collisionEvent.getEntity();
        itemComponent = _entityManager->getComponentFromEntity<ItemComponent>(item);
    }
    itemComponent->getLamda()(*_entityManager, collisionEvent);
    _entityManager->addComponentToEntity<DamageableComponent>(item);
    _entityManager->getComponentFromEntity<DamageableComponent>(item)->destroy();
}

void PowerupSystem::update(double deltaTime) {

}

void PowerupSystem::handleTurnSwitchedEvent(const TurnSwitchedEvent &turnSwitchedEvent) {
    Random random;
    if (random.between(0,1) == 0) { spawnDrop(_itemMap);}
    spawnDrop(_weaponMap);
}


