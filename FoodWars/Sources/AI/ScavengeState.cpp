#include <utility>
#include "../../Headers/AI/ScavengeState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/AI/AttackState.h"
#include <iostream>
#include <math.h>

void ScavengeState::enter() {
    std::cout << "Entering scavenge state" << std::endl;
}

void ScavengeState::execute(double dt) {
    // if not my turn, switch to idle state
    // if my turn, calculate new state

    if(!_turnComponent->isMyTurn() || (_positionComponent->X <= _targetPosition.X && _positionComponent->X + _boxCollider->width >= _targetPosition.X)){
        // Idle state
        _aiComponent->setCurrentState(std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return;
    }
    moveToTarget(dt);
}

void ScavengeState::exit() {

}

ScavengeState::ScavengeState(EntityManager &entityManager, int entityId, const PositionComponent& targetPosition, AISystem &context) : State(entityManager,
                                                                                            entityId,
                                                                                            context),
                                                                                      CollisionEventHandler(context.getCollisionEventObservable()), _targetPosition(targetPosition) {

}

void ScavengeState::walkLeft(double dt) {
    _moveComponent->xVelocity = -100;
    _turnComponent->lowerEnergy(_walkingEnergyCostPerSecond * dt);
}

void ScavengeState::walkRight(double dt) {
    _moveComponent->xVelocity = 100;
    _turnComponent->lowerEnergy(_walkingEnergyCostPerSecond * dt);
}

void ScavengeState::moveToTarget(double dt){
    // Correct X Position
    if(_positionComponent->X <= _targetPosition.X && _positionComponent->X + _boxCollider->width >= _targetPosition.X)
        _moveComponent->xVelocity = 0;
        // Incorrect X Position
    else{
        if(_positionComponent->X > _targetPosition.X)
            walkLeft(dt);
        else if(_positionComponent->X < _targetPosition.X)
            walkRight(dt);
    }
}


void ScavengeState::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    // what to do now
    //std::cout << "boop" << std::endl;
    jump();
    // Check if its the side of a block


}

bool ScavengeState::canHandle(const CollisionEvent &collisionEvent) {
    //if(collisionEvent.getEntity() == _entityId || collisionEvent.getOtherEntity() == _entityId)


    // TODO: KEEP BELOW
    return collisionEvent.getCollisionAngle() <= 315 && collisionEvent.getCollisionAngle() >= 45;
}