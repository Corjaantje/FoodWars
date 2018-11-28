#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/AIComponent.h"

AISystem::AISystem(std::shared_ptr<EntityManager> entityManager, IObservable<CollisionEvent>& collisionEventObservable){
    _entityManager = std::move(entityManager);
    autoClimbOnCollision  = new CollisionEventHandlerLamda {
            collisionEventObservable,
            // Staircase walking
            /*[entityManager = _entityManager](const CollisionEvent& collisionEvent) {
                double angle = collisionEvent.getCollisionAngle();
                return (angle >= 45 && angle <= 135) || (angle >= 225 && angle <= 315);
            } ,*/
            [](const CollisionEvent& collisionEvent){
                return false;
            },
            [entityManager = _entityManager](const CollisionEvent& collisionEvent) {
                auto moveComponent = entityManager->getComponentFromEntity<MoveComponent>(collisionEvent.getEntity());
                auto boxCollider = entityManager->getComponentFromEntity<BoxCollider>(collisionEvent.getEntity());
                auto positionComponent = entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getEntity());
                auto otherPositionComponent = entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getOtherEntity());
                if(std::abs(positionComponent->Y + boxCollider->height/2) < otherPositionComponent->Y) {
                    //moveComponent->yVelocity = 0;
                    positionComponent->Y = otherPositionComponent->Y - boxCollider->height;
                }
            }
    };
}

AISystem::~AISystem() {
    delete autoClimbOnCollision;
}


void AISystem::update(double dt) {
    const int walkingEnergyCostPerSecond = 20;
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
        auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);

        if (turnComponent->isMyTurn()) {
            // Check for what to do
            moveComponent->xVelocity = -100;
            turnComponent->lowerEnergy(walkingEnergyCostPerSecond * dt);

           /* if (_pressedKey == KEY::KEY_A) {
                moveComponent->xVelocity = -100;
                iterator.second->lowerEnergy(walkingEnergyCostPerSecond * dt);
            }
            else if (_pressedKey == KEY::KEY_D) {
                moveComponent->xVelocity = 100;
                iterator.second->lowerEnergy(walkingEnergyCostPerSecond * dt);
            }else
                moveComponent->xVelocity = 0;*/
        } else {
            moveComponent->xVelocity = 0;
        }
    }

    for (auto const &iterator: _entityManager->getAllEntitiesWithComponent<MoveComponent>()) {
        std::shared_ptr<MoveComponent> moveComponent = iterator.second;
        std::shared_ptr<PositionComponent> positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if(positionComponent) {
            positionComponent->X += std::round(dt * moveComponent->xVelocity);
            positionComponent->Y += std::round(dt * moveComponent->yVelocity);
        }
    }

    // TODO: Jump

}

