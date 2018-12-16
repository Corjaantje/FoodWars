#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"
#include "../../../Headers/AI/IdleState.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"

AISystem::AISystem(EntityManager &entityManager, AudioFacade& audioFacade, IObservable<CollisionEvent>& collisionEventObservable)
                                        : _entityManager(&entityManager), _collisionEventObservable(&collisionEventObservable), _audioFacade(&audioFacade){
    for(const auto iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        iterator.second->setCurrentState(std::make_unique<IdleState>(*_entityManager, iterator.first, "", *this));
    }
}

AISystem::~AISystem() = default;

int AISystem::generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                                        double velocityX, double velocityY, Weapon* selectedWeapon) {
    int projectile = _entityManager->createEntity();
    int projectileWidth = 11;
    int projectileHeight = 32;
    double playerCenterX = playerPositionComponent.X + playerCollider.width / 2.0;
    double playerCenterY = playerPositionComponent.Y + playerCollider.height / 2.0;
    int posX = playerCenterX;
    int posY = playerCenterY;
    // Checks for shooting down
    if (velocityX > 0 && velocityY > 70) posY = playerCenterY + 50;
    else if (velocityX <= 0 && velocityY > 70) posY = playerCenterY + 50;
        // Checks for shooting up
    else if (velocityX > 0 && velocityY <= -70) posY = playerCenterY - 50;
    else if (velocityX <= 0 && velocityY <= -70) posY = playerCenterY - 50;
        // Remaining default checks
    else if (velocityX > 0) posX += projectileWidth + playerCollider.width + 1;
    else posX -= projectileWidth + playerCollider.width + 1;
    if (velocityY < 0) posY -= projectileHeight + 1;

    std::cout << "VelocityX: " << velocityX << ", VelocityY: " << velocityY << std::endl;

    const double speedModifier = 2.5;

    _entityManager->addComponentToEntity<DrawableComponent>(projectile, std::make_unique<ShapeSprite>(projectileWidth,
                                                                                                       projectileHeight,
                                                                                                       posX, posY,
                                                                                                       selectedWeapon->getImage()));
    _entityManager->addComponentToEntity<PositionComponent>(projectile, posX, posY);
    _entityManager->addComponentToEntity<BoxCollider>(projectile, projectileWidth, projectileHeight);
    _entityManager->addComponentToEntity<DamagingComponent>(projectile, 25, selectedWeapon->getFaction());
    _entityManager->addComponentToEntity<DamageableComponent>(projectile, 10);
    _entityManager->addComponentToEntity<GravityComponent>(projectile, 6 * speedModifier);
    _entityManager->addComponentToEntity<MoveComponent>(projectile, velocityX * speedModifier,
                                                        velocityY * speedModifier);
    //selectedWeapon->lowerAmmo();
    return projectile;
}

void AISystem::update(double dt) {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
        auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        iterator.second->update(dt);
    }
}

IObservable<CollisionEvent> &AISystem::getCollisionEventObservable() {
    return *_collisionEventObservable;
}