#include <utility>
#include "../../Headers/AI/WanderState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Components/ItemComponent.h"

void WanderState::enter() {
    std::cout << "Entering wandering state" << std::endl;
}

void WanderState::execute(double dt) {
    // if not my turn, switch to idle state
    if (!_turnComponent->isMyTurn()
        || _turnComponent->getRemainingTime() <= 0
        || _turnComponent->getEnergy() <= 0.0
        || !_positionComponent
        || (_positionComponent->X <= _targetPosition.X &&
            _positionComponent->X + _boxCollider->width >= _targetPosition.X &&
            _positionComponent->Y <= _targetPosition.Y &&
            _positionComponent->Y + _boxCollider->height >= _targetPosition.Y)
        || !canReachTarget
        || (_target != nullptr && !_target->isAlive())) {
        // Idle state
        _aiComponent->setCurrentState(
                std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return;
    }
    // If my turn, move towards target
    moveToTarget(dt);
}

void WanderState::exit() {

}

WanderState::WanderState(EntityManager &entityManager, int entityId, const PositionComponent &targetPosition,
                         const DamageableComponent *target, AISystem &context)
        : State(entityManager, entityId, context),
          CollisionEventHandler(context.getCollisionEventObservable()), _targetPosition(targetPosition),
          movedTarget{false},
          _target{target} {

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
void WanderState::moveToTarget(double dt) {
    // Correct X Position
    int xDiff = _positionComponent->X - _targetPosition.X;
    if (xDiff <= -5)
        walkRight(dt);
    else if (xDiff >= 5)
        walkLeft(dt);
    else if (!movedTarget && _targetPosition.Y > 0 &&
             (_targetPosition.Y + _boxCollider->width / 2.0) - _positionComponent->Y > 0) { //target is onder speler
        std::cout << "Change target" << std::endl;
        if (_targetPosition.X < _positionComponent->X) { //target links van speler
            _targetPosition.X -= _boxCollider->width;
        } else if (_targetPosition.X > _positionComponent->X)
            _targetPosition.X += _boxCollider->width;
        movedTarget = true;
        moveToTarget(dt);
    } else { //kan niet bij het target
        std::cout << "Can't reach target" << std::endl;
        canReachTarget = false;
    }
}

bool WanderState::canHandle(const CollisionEvent &collisionEvent) {
    //check if collision with an item. When an item is picked up go to idle state
    if ((collisionEvent.getOtherEntity() == _entityId &&
         _entityManager->getComponentFromEntity<ItemComponent>(collisionEvent.getEntity())) ||
        (collisionEvent.getEntity() == _entityId &&
         _entityManager->getComponentFromEntity<ItemComponent>(collisionEvent.getOtherEntity()))) {
        _aiComponent->setCurrentState(
                std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return false;
    }

    return ((collisionEvent.getCollisionAngle() <= 135 && collisionEvent.getCollisionAngle() >= 45) ||
            (collisionEvent.getCollisionAngle() <= 315 && collisionEvent.getCollisionAngle() >= 225))
           && ((collisionEvent.getEntity() == _entityId &&
                !_entityManager->getComponentFromEntity<ItemComponent>(collisionEvent.getOtherEntity())) ||
               (collisionEvent.getOtherEntity() == _entityId &&
                !_entityManager->getComponentFromEntity<ItemComponent>(collisionEvent.getEntity())));
}

void WanderState::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    // already jumping
    if (_entityManager->getComponentFromEntity<JumpComponent>(_entityId)) return;

    // jump over block
    int obstructionId;
    (collisionEvent.getEntity() == _entityId) ? obstructionId = collisionEvent.getOtherEntity()
                                              : obstructionId = collisionEvent.getEntity();
    auto targetDamageable = _entityManager->getComponentFromEntity<DamageableComponent>(obstructionId);

    if (canJumpOverObstruction(obstructionId)) {
        jump();
    } else if (targetDamageable &&
               _entityManager->getComponentFromEntity<PlayerComponent>(_entityId)->getTotalAmmoCount()) {
        // Attack obstruction
        auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(obstructionId);
        _aiComponent->setCurrentState(
                std::make_unique<AttackState>(*_entityManager, _entityId, obstructionId, *targetPosition,
                                              *targetDamageable, *_context));
        return;
    } else {
        _turnComponent->setEnergy(0.0);
    }
}

// Returns wether the AI can jump over an obstruction or not
bool WanderState::canJumpOverObstruction(int obstructionId) {
    auto obstructionPosition = _entityManager->getComponentFromEntity<PositionComponent>(obstructionId);
    // check if there are blocks above the obstruction
    for (const auto &iterator : _entityManager->getAllEntitiesWithComponent<BoxCollider>()) {
        auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        //todo: might have to change the 64
        auto aiPosition = _entityManager->getComponentFromEntity<PositionComponent>(_entityId);

        if ((positionComponent->X == obstructionPosition->X
             && positionComponent->Y >= obstructionPosition->Y - 64
             && (positionComponent->Y <= aiPosition->Y &&
                 !_entityManager->getComponentFromEntity<PlayerComponent>(obstructionId)))) {
            // cant jump
            return false;
        }
    }
    return true;
}