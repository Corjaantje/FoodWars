#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"
#include "../../../Headers/AI/WanderState.h"
#include "../../../Headers/AI/IdleState.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"

AISystem::AISystem(EntityManager &entityManager, AudioFacade& audioFacade, IObservable<CollisionEvent>& collisionEventObservable)
                                        : _entityManager(&entityManager), _collisionEventObservable(&collisionEventObservable), _audioFacade(&audioFacade){
    for(const auto iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        iterator.second->setCurrentState(std::make_unique<IdleState>(*_entityManager, iterator.first, *this));
    }
}

AISystem::~AISystem() = default;

int AISystem::generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                                        double velocityX, double velocityY) {
    int _projectile = _entityManager->createEntity();
    int projectileWidth = 11;
    int projectileHeight = 32;
    int posX = playerPositionComponent.X;
    int posY = playerPositionComponent.Y;
    if (velocityX > 0) posX += projectileWidth + playerCollider.width + 1;
    else posX -= projectileWidth + 1;
    if (velocityY < 0) posY -= projectileHeight + 1;

    std::cout << "VelocityX: " << velocityX << ", VelocityY: " << velocityY << std::endl;

    const double speedModifier = 2.5;
    _entityManager->addComponentToEntity<DrawableComponent>(_projectile, std::make_unique<ShapeSprite>(projectileWidth,
                                                                                                       projectileHeight,
                                                                                                       posX, posY,
                                                                                                       "carrot.png"));
    _entityManager->addComponentToEntity<PositionComponent>(_projectile, posX, posY);
    _entityManager->addComponentToEntity<BoxCollider>(_projectile, projectileWidth, projectileHeight);
    _entityManager->addComponentToEntity<DamagingComponent>(_projectile, 25);
    _entityManager->addComponentToEntity<DamageableComponent>(_projectile, 10);
    _entityManager->addComponentToEntity<GravityComponent>(_projectile, 6.5 * speedModifier);
    _entityManager->addComponentToEntity<MoveComponent>(_projectile, velocityX * speedModifier,
                                                        velocityY * speedModifier);
    return _projectile;
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