#include <utility>
#include <iostream>
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../Headers/AI/IdleState.h"
#include <math.h>

AttackState::AttackState(EntityManager &entityManager, int entityId, const PositionComponent &targetPosition,
                         const DamageableComponent &target,
                         AISystem &context) : State(entityManager,
                                                    entityId,
                                                    context),
                                              CollisionEventHandler(context.getCollisionEventObservable()),
                                              _targetPosition(targetPosition),
                                              _target{&target} {

}

void AttackState::enter() {
    std::cout << "Entering attack state" << std::endl;
}

void AttackState::execute(double dt) {
    if(!_turnComponent->isMyTurn()
       || _turnComponent->getRemainingTime() <= 0
       || _turnComponent->getEnergy() <= 0.0
       || !_target
       || !_target->isAlive()) {
        //todo: Check Ammo count
        _aiComponent->setCurrentState(std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return;
    }
    if (!_projectileFired) {
        double centerX = _positionComponent->X + _boxCollider->width/2.0;
        double centerY = _positionComponent->Y + _boxCollider->height/2.0;
        double distance = std::abs(centerX - _targetPosition.X);
        double force = -0.00024 * std::pow(distance, 2) + 0.47 * distance + 6.0;
        _turnComponent->lowerEnergy(20);
        _context->generateProjectile(*_entityManager->getComponentFromEntity<PositionComponent>(_entityId),
                                     *_entityManager->getComponentFromEntity<BoxCollider>(_entityId), centerX > _targetPosition.X ? -force : force, force < 0 ? force : -force);
        _projectileFired = true;
    }
}

void AttackState::exit() {

}

void AttackState::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    _projectileFired = false;
}

bool AttackState::canHandle(const CollisionEvent &collisionEvent) {
    int target = collisionEvent.getEntity();
    int projectile = collisionEvent.getOtherEntity();

    return _projectileFired && _entityManager->getComponentFromEntity<DamagingComponent>(target)/* &&
                               _entityManager->getComponentFromEntity<DamageableComponent>(projectile)*/;
}
