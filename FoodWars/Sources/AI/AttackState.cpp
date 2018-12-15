#include <utility>
#include <iostream>
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../TonicEngine/Headers/Visual/Colour.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../Headers/GameECS/Systems/Misc/ProjectileBuilder.h"

AttackState::AttackState(EntityManager &entityManager, int entityId, int targetId,
                         const PositionComponent &targetPosition,
                         const DamageableComponent &target,
                         AISystem &context) : State(entityManager,
                                                    entityId,
                                                    context),
                                              CollisionEventHandler(context.getCollisionEventObservable()),
                                              _targetId{targetId},
                                              _targetPosition(targetPosition),
                                              _target{&target},
                                              _shootingSimulator{context.getCollisionEventObservable(), entityManager,
                                                                 [this](const ShotTry &shotTry, bool directHit) {
                                                                     std::cout << "Shot found! " << std::endl;
                                                                     shotFound(shotTry, directHit);
                                                                 }} {

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
        _aiComponent->setCurrentState(std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return;
    }
    if (!_projectileFired) {
        if (_turnComponent->getEnergy() < 20) {
            _turnComponent->setRemainingTime(0);
            return;
        }
        if (!_canHitTarget) {
            _shootingSimulator.tryHitting(_entityId, _targetId);
        } else
            fireProjectile(_directHit);
        _projectileFired = true;
    }
}

void AttackState::exit() {
    _shootingSimulator.cleanup();
}

void AttackState::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    _projectileFired = false;
    std::cout << "projectile collided!" << std::endl;
    _projectileId = -1;
}

bool AttackState::canHandle(const CollisionEvent &collisionEvent) {
    return _projectileFired && (collisionEvent.getEntity() == _projectileId || collisionEvent.getOtherEntity() == _projectileId);
}

void AttackState::shotFound(ShotTry shotTry, bool directHit) {
    _shootingSimulator.cleanup();
    _canHitTarget = directHit;
    if (_canHitTarget)
        _directHit = shotTry;
    fireProjectile(shotTry);
}

void AttackState::fireProjectile(const ShotTry &shotTry) {
    std::cout << "Firing projectile..." << std::endl;
    _projectileFired = true;
    auto playerComponent = _entityManager->getComponentFromEntity<PlayerComponent>(_entityId);
    Weapon *selectedWeapon = playerComponent->getSelectedWeapon();

    for (int i = playerComponent->getAmountOFWeapons(); i > 0; i--) {
        selectedWeapon = playerComponent->getSelectedWeapon();
        if (selectedWeapon->getAmmo() > 0) break;
        playerComponent->setSelectedWeapon("next");
    }

    //todo: energy
    if (selectedWeapon->getAmmo() <=
        0 /*|| _entityManager->getComponentFromEntity<TurnComponent>(_entityId)->getEnergy() < 20*/)
        return;

    _turnComponent->lowerEnergy(20);
    selectedWeapon->lowerAmmo();
    ProjectileBuilder projectileBuilder{*_entityManager};
    _projectileId = projectileBuilder
            .setShootingAngle(shotTry.getAngle())
            .setYVelocity(shotTry.getYVelocity())
            .setXVelocity(shotTry.getXVelocity())
            .setPower(shotTry.getPower())
            .setWeapon(*selectedWeapon)
            .setPlayerCollider(*_boxCollider)
            .setPlayerPostion(*_positionComponent)
            .build();
}