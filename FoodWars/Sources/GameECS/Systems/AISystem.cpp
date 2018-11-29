#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"

AISystem::AISystem(std::shared_ptr<EntityManager> entityManager, const std::shared_ptr<AudioFacade>& audioFacade, IObservable<CollisionEvent>& collisionEventObservable){
    _entityManager = std::move(entityManager);
    _audioFacade = audioFacade;
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

            auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
            if(positionComponent) {
                positionComponent->X += std::round(dt * moveComponent->xVelocity);
                positionComponent->Y += std::round(dt * moveComponent->yVelocity);
            }
        } else {
            moveComponent->xVelocity = 0;
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


