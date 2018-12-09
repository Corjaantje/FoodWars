#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"
#include "../../../Headers/AI/ScavengeState.h"
#include "../../../Headers/AI/IdleState.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"

AISystem::AISystem(EntityManager &entityManager, AudioFacade& audioFacade, IObservable<CollisionEvent>& collisionEventObservable)
                                        : _entityManager(&entityManager), _collisionEventObservable(collisionEventObservable), _audioFacade(&audioFacade){
    for(const auto iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        iterator.second->setCurrentState(std::make_unique<IdleState>(*_entityManager, iterator.first, *this));
    }
}

AISystem::~AISystem() = default;

void AISystem::generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
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
}

void AISystem::update(double dt) {

    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
        auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);

        iterator.second->update(dt);

        /*if (!turnComponent->isMyTurn()) {
            iterator.second->
            iterator.second->update(dt);
        }
        else {
            // TODO: Choose a state


            // Scavenge
            // TODO: Check for nearby items
            iterator.second->setCurrentState(std::make_unique<ScavengeState>(_entityManager, _audioFacade, iterator.first, _collisionEventObservable));
            iterator.second->update(dt);

            // Attack
            // TODO: if stronger than enemy

            // Flee
            // TODO: if weaker than enemy
        }*/
            //jump(iterator.first, *turnComponent);
            //walkRight(*moveComponent, *turnComponent, dt);
            //walkLeft(*moveComponent, *turnComponent, dt);






            /*if(moveComponent->xVelocity >= 0)
            {
                walkRight(*moveComponent, *turnComponent, dt);
            }
            std::cout << "Distance to enemy: " << getDistanceToEnemy(iterator.first) << std::endl;
            if(getDistanceToEnemy(iterator.first) < 800)
            {
                // TODO: Shoot towards enemy


            }
            auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
            if(positionComponent) {
                positionComponent->X += std::round(dt * moveComponent->xVelocity);
                positionComponent->Y += std::round(dt * moveComponent->yVelocity);
            }
        } else {
            moveComponent->xVelocity = 0;
        }*/
    }
}

IObservable<CollisionEvent> &AISystem::getCollisionEventObservable() {
    return _collisionEventObservable;
}



/*
int AISystem::getDistanceToEnemy(int entityId) {
    for(const auto &iterator : _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        return calculateDistance(entityId, iterator.first);
    }
    // Player not found
    return 0;
}

// Calculates the manhattan distance between the centers two entities
int AISystem::calculateDistance(int entityOne, int entityTwo) {
    auto positionComponentOne = _entityManager->getComponentFromEntity<PositionComponent>(entityOne);
    auto positionComponentTwo = _entityManager->getComponentFromEntity<PositionComponent>(entityTwo);

    auto boxColliderOne = _entityManager->getComponentFromEntity<BoxCollider>(entityOne);
    auto boxColliderTwo = _entityManager->getComponentFromEntity<BoxCollider>(entityTwo);

    countObstructingBlocks(positionComponentOne, positionComponentTwo);
    return 0; //abs((positionComponentOne->X + boxColliderOne->width) - (positionComponentTwo->X + boxColliderTwo->width)) + abs((positionComponentOne->Y + boxColliderOne->height) - (positionComponentTwo->Y + boxColliderTwo->height));
}

// List of entities between two points
int AISystem::countObstructingBlocks(PositionComponent* posOne, PositionComponent* posTwo){
    std::vector<int> obstructingBlocks;
    for(const auto& iterator: _entityManager->getAllEntitiesWithComponent<BoxCollider>())
    {
        auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        // get all items between two points
        if((positionComponent->X >= posOne->X && positionComponent->X <= posTwo->X && positionComponent->Y >= posOne->Y && positionComponent->Y <= posTwo->Y) // two is bottom right of one
        || (positionComponent->X >= posOne->X && positionComponent->X <= posTwo->X && positionComponent->Y <= posOne->Y && positionComponent->Y >= posTwo->Y) // two is top right of one
        || (positionComponent->X <= posOne->X && positionComponent->X >= posTwo->X && positionComponent->Y >= posOne->Y && positionComponent->Y <= posTwo->Y) // two is bottom left of one
        || (positionComponent->X <= posOne->X && positionComponent->X >= posTwo->X && positionComponent->Y <= posOne->Y && positionComponent->Y >= posTwo->Y)) // two is top left of one
        {
            obstructingBlocks.push_back(iterator.first);
        }
    }
    // print entity Id's
    */
/*for(int i : obstructingBlocks){
        std::cout << "entityId: " << i << std::endl;
    }*//*


    return 0;
}*/
