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

PowerupSystem::PowerupSystem(IObservable<CollisionEvent> &collisionEventObservable, EntityManager &entityManager)
        : CollisionEventHandler(collisionEventObservable), _entityManager{&entityManager}, _itemFactory{ItemFactory{}}{
    _itemMap[0] = "cake";
    _itemMap[1] = "painkiller";
    spawnPowerup();
}

void PowerupSystem::spawnPowerup() {
    Random random;

    // 50/50 chance of powerup spawning
    if (random.between(0,1) == 0) {
        //min 29
        int itemX = random.between(0,1571);
        int itemY = 0;

        int powerup = _entityManager->createEntity();
        int weaponChance = random.between(0,1);

        // Random powerup
        auto item = _itemFactory.createItem(_itemMap[weaponChance]);
        _entityManager->addComponentToEntity(powerup, std::make_unique<ItemComponent>(item));
        _entityManager->addComponentToEntity<DrawableComponent>(powerup,
                                                                std::make_unique<ShapeSprite>(29, 42, itemX, itemY,
                                                                                              item.getItemName() +
                                                                                              ".png"));
        _entityManager->addComponentToEntity<BoxCollider>(powerup, 29, 42);
        _entityManager->addComponentToEntity<PositionComponent>(powerup, itemX, itemY);
        _entityManager->addComponentToEntity<GravityComponent>(powerup, 5);
    }
}

bool PowerupSystem::canHandle(const CollisionEvent &collisionEvent) {
    int player = collisionEvent.getEntity();
    int item = collisionEvent.getOtherEntity();
    return _entityManager->getComponentFromEntity<PlayerComponent>(player) &&
           _entityManager->getComponentFromEntity<ItemComponent>(item);
}

void PowerupSystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    int item = collisionEvent.getOtherEntity();
    auto tekkel = _entityManager->getComponentFromEntity<ItemComponent>(item);

    auto test = tekkel->getLamda();
    auto lambda = [](EntityManager& e, const CollisionEvent& event)
    {
        e.getComponentFromEntity<DamageableComponent>(event.getEntity())->increaseHealth(50);
        e.removeEntity(event.getOtherEntity());
    };
    lambda(*_entityManager, collisionEvent);
}

void PowerupSystem::update(double deltaTime) {

}
