#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"

AISystem::AISystem(std::shared_ptr<EntityManager> entityManager, const std::shared_ptr<AudioFacade>& audioFacade, IObservable<CollisionEvent>& collisionEventObservable){
    _entityManager = std::move(entityManager);
    _audioFacade = audioFacade;

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

    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
        auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);

        if (turnComponent->isMyTurn()) {

            //jump(iterator.first, *turnComponent);
            //walkRight(*moveComponent, *turnComponent, dt);
            walkLeft(*moveComponent, *turnComponent, dt);
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
}

void AISystem::jump(int entityId, TurnComponent& turnComponent){
    if(!_entityManager->getComponentFromEntity<JumpComponent>(entityId)) {
        _entityManager->addComponentToEntity(entityId, new JumpComponent);
        turnComponent.lowerEnergy(5);
        _audioFacade->playEffect("jump");
    }
}

void AISystem::walkLeft(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt) {
    moveComponent.xVelocity = -100;
    turnComponent.lowerEnergy(walkingEnergyCostPerSecond * dt);
}

void AISystem::walkRight(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt) {
    moveComponent.xVelocity = 100;
    turnComponent.lowerEnergy(walkingEnergyCostPerSecond * dt);
}


