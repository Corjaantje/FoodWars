#include <utility>
#include <iostream>
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../TonicEngine/Headers/Visual/Colour.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
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
    int targetEntity = _entityManager->createEntity();
    _entityManager->addComponentToEntity<PositionComponent>(targetEntity, _targetPosition.X, _targetPosition.Y);
    _entityManager->addComponentToEntity<DrawableComponent>(targetEntity, std::make_unique<ShapeRectangle>(10, 10, _targetPosition.X, _targetPosition.Y, Colour{255, 0, 0, 255}));
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
        std::cout << "ALLAHU AKBAR" << std::endl;
        _projectileId = _context->generateProjectile(*_entityManager->getComponentFromEntity<PositionComponent>(_entityId),
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
    return _projectileFired && (collisionEvent.getEntity() == _projectileId || collisionEvent.getOtherEntity() == _projectileId);
}
