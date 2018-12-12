#include "../../../Headers/GameECS/Systems/PowerupSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/StateMachine/Misc/Coordinate.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/ItemComponent.h"

PowerupSystem::PowerupSystem(IObservable<CollisionEvent> &collisionEventObservable, EntityManager &entityManager)
        : CollisionEventHandler(collisionEventObservable), _entityManager{&entityManager} {
    spawnPowerup();
}

void PowerupSystem::spawnPowerup() {

    Random random;
    int spawnChance = random.between(0,1);

    // 50/50 chance of powerup spawning
    if (spawnChance == 0) {
        std::string image;

        int weaponChance = random.between(0,1);

        // Random powerup
        if (weaponChance == 0) {
            image = "cake.png";
        } else if (weaponChance == 1) {
            image = "painkiller.png";
        }

        int spawnPointX = random.between(0,1571);
        int spawnPointY = 0;

        Coordinate spawnPoint;
        spawnPoint.setCoordinates(spawnPointX,spawnPointY);

        // Powerup
        int powerup = _entityManager->createEntity();
        _entityManager->addComponentToEntity<DrawableComponent>(powerup, std::make_unique<ShapeSprite>(29, 42,
                                                                                                       spawnPoint.getXCoord(),
                                                                                                       spawnPoint.getYCoord(),
                                                                                                       image));
        _entityManager->addComponentToEntity<BoxCollider>(powerup, 29, 42);
        _entityManager->addComponentToEntity<PositionComponent>(powerup, spawnPoint.getXCoord(), spawnPoint.getYCoord());
        _entityManager->addComponentToEntity<GravityComponent>(powerup);
        _entityManager->addComponentToEntity<ItemComponent>(powerup);
    }
}

bool PowerupSystem::canHandle(const CollisionEvent &collisionEvent) {
    int player = collisionEvent.getEntity();
    int item = collisionEvent.getOtherEntity();
    return _entityManager->getComponentFromEntity<PlayerComponent>(player) &&
           _entityManager->getComponentFromEntity<ItemComponent>(item);
}

void PowerupSystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    auto player = _entityManager->getComponentFromEntity<PlayerComponent>(collisionEvent.getEntity());
    auto item = _entityManager->getComponentFromEntity<ItemComponent>(collisionEvent.getOtherEntity());


}

void PowerupSystem::update(double deltaTime) {

}
