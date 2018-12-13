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
    spawnPowerup();
}

void PowerupSystem::spawnPowerup() {
    Random random;

    // 50/50 chance of powerup spawning
    if (random.between(0,1) == 0) {
        int itemY = 0;
        int itemWidth = 29;
        int itemHeight = 42;
        int itemX = random.between(0,1600-itemWidth);

        int powerup = _entityManager->createEntity();
        int powerupChance = random.between(0,_itemFactory.getMapSize()-1);

        // Random powerup
        std::string sTest = _itemMap[powerupChance];
        auto item = _itemFactory.createItem(_itemMap[powerupChance]);
        _entityManager->addComponentToEntity(powerup, std::make_unique<ItemComponent>(item));
        _entityManager->addComponentToEntity<DrawableComponent>(powerup,
                                                                std::make_unique<ShapeSprite>(itemWidth, itemHeight, itemX, itemY,
                                                                                              item.getItemName() +
                                                                                              ".png"));
        _entityManager->addComponentToEntity<BoxCollider>(powerup, itemWidth, itemHeight);
        _entityManager->addComponentToEntity<PositionComponent>(powerup, itemX, itemY);
        _entityManager->addComponentToEntity<GravityComponent>(powerup, 5);
        _entityManager->addComponentToEntity<DamageableComponent>(powerup, 1);
    }
}

void PowerupSystem::spawnWeapon() {
    Random random;

    int weaponX = random.between(0, 1571);
    int weaponY = 0;
    int weaponWidth = 29;
    int weaponHeight = 42;

    int weaponID = _entityManager->createEntity();
    // TODO: Create another factory or change the range hardcoded?
    int weaponChance = random.between(0, _weaponFactory.getMapSize()-1);

    std::string sTest = _weaponMap[weaponChance];
    auto weaponType = _weaponFactory.createItem(_weaponMap[weaponChance]);
    _entityManager->addComponentToEntity(weaponID, std::make_unique<ItemComponent>(weaponType));
    // TODO: better sprite for representing a weapon drop
    _entityManager->addComponentToEntity<DrawableComponent>(weaponID,
                                                            std::make_unique<ShapeSprite>(weaponWidth, weaponHeight, weaponX, weaponY,
                                                                                          weaponType.getItemName() +
                                                                                          ".png"));
    _entityManager->addComponentToEntity<BoxCollider>(weaponID, weaponWidth, weaponHeight);
    _entityManager->addComponentToEntity<PositionComponent>(weaponID, weaponX, weaponY);
    _entityManager->addComponentToEntity<GravityComponent>(weaponID, 5);
    _entityManager->addComponentToEntity<DamageableComponent>(weaponID, 1);
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
    spawnWeapon();
    spawnPowerup();
}
