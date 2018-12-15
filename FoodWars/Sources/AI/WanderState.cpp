#include <utility>
#include "../../Headers/AI/WanderState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/AI/AttackState.h"

void WanderState::enter() {
    std::cout << "Entering scavenge state" << std::endl;
}

void WanderState::execute(double dt) {
    // if not my turn, switch to idle state
    if(!_turnComponent->isMyTurn()
    || _turnComponent->getRemainingTime() <= 0
    || _turnComponent->getEnergy() <= 0.0
    || (_positionComponent->X <= _targetPosition.X && _positionComponent->X + _boxCollider->width >= _targetPosition.X)){
        // Idle state
        _aiComponent->setCurrentState(std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return;
    }
    // If my turn, move towards target
    moveToTarget(dt);
}

void WanderState::exit() {

}

WanderState::WanderState(EntityManager &entityManager, int entityId, const PositionComponent& targetPosition, AISystem &context) : State(entityManager,
                                                                                            entityId,
                                                                                            context),
                                                                                      CollisionEventHandler(context.getCollisionEventObservable()), _targetPosition(targetPosition) {

}

// Makes the AI walk left
void WanderState::walkLeft(double dt) {
    _moveComponent->xVelocity = -100;
    _turnComponent->lowerEnergy(_walkingEnergyCostPerSecond * dt);
}

// Makes the AI walk right
void WanderState::walkRight(double dt) {
    _moveComponent->xVelocity = 100;
    _turnComponent->lowerEnergy(_walkingEnergyCostPerSecond * dt);
}

// Makes the AI walk towards its target
void WanderState::moveToTarget(double dt){
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

bool WanderState::canHandle(const CollisionEvent &collisionEvent) {
    return (collisionEvent.getCollisionAngle() <= 135 && collisionEvent.getCollisionAngle() >= 45) || (collisionEvent.getCollisionAngle() <= 315 && collisionEvent.getCollisionAngle() >= 225);
}

void WanderState::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    // already jumping
    if(_entityManager->getComponentFromEntity<JumpComponent>(_entityId)) return;

    // jump over block
    int obstructionId;
    (collisionEvent.getEntity() == _entityId) ? obstructionId = collisionEvent.getOtherEntity() : obstructionId = collisionEvent.getEntity();

    if (canJumpOverObstruction(obstructionId)) {
        jump();
    } else {
        // Attack obstruction
        auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(obstructionId);
        auto targetDamageable = _entityManager->getComponentFromEntity<DamageableComponent>(obstructionId);
        _aiComponent->setCurrentState(
                std::make_unique<AttackState>(*_entityManager, _entityId, obstructionId, *targetPosition,
                                              *targetDamageable, *_context));
        return;
    }
}

// Returns wether the AI can jump over an obstruction or not
bool WanderState::canJumpOverObstruction(int obstructionId) {
    auto obstructionPosition = _entityManager->getComponentFromEntity<PositionComponent>(obstructionId);
    // check if there are blocks above the obstruction
    for(const auto &iterator : _entityManager->getAllEntitiesWithComponent<BoxCollider>()) {
        auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        //todo: might have to change the 64
        auto aiPosition = _entityManager->getComponentFromEntity<PositionComponent>(_entityId);

        if((positionComponent->X == obstructionPosition->X
        && positionComponent-> Y >= obstructionPosition->Y - 64
        && positionComponent->Y <= aiPosition->Y)){
            // cant jump
            return false;
        }
    }
    return true;
}