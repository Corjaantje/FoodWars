#include <utility>
#include <iostream>
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../TonicEngine/Headers/Visual/Colour.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../Headers/GameECS/Systems/Misc/ProjectileBuilder.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../../TonicEngine/Headers/General/Random.h"

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
                                              _shootingLine{entityManager},
                                              _powerBar{entityManager},
                                              _random{},
                                              _shootingSimulator{context.getCollisionEventObservable(), entityManager,
                                                                 [this](const ShotTry &shotTry, bool directHit) {
                                                                     shotFound(shotTry, directHit);
                                                                 }} {
    _configBasedOnDifficulty[Difficulty::EASY] = ShootingSimulatorConfig{27, 15.0};
    _configBasedOnDifficulty[Difficulty::MEDIUM] = ShootingSimulatorConfig{15, 10.0};
    _configBasedOnDifficulty[Difficulty::HARD] = ShootingSimulatorConfig{5.0, 8.0};
    _configBasedOnDifficulty[Difficulty::INSANE] = ShootingSimulatorConfig{2, 2.0};
    _deviationBasedOnDifficulty[Difficulty::EASY] = 10.0;
    _deviationBasedOnDifficulty[Difficulty::MEDIUM] = 5;
    _deviationBasedOnDifficulty[Difficulty::HARD] = 1;
    _deviationBasedOnDifficulty[Difficulty::INSANE] = 0;
}

void AttackState::enter() {

}

void AttackState::execute(double dt) {
    if(!_turnComponent->isMyTurn()
       || _turnComponent->getRemainingTime() <= 0
       || _turnComponent->getEnergy() <= 20.0
       || !hasAmmo()
       || !_target
       || !_target->isAlive()) {
        _aiComponent->setCurrentState(std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return;
    }
    if (!_projectileFired) {
        if (_turnComponent->getEnergy() < 20) {
            //_turnComponent->setRemainingTime(0);
            return;
        }
        if (!_canHitTarget) {
            // todo: difficulty
            std::cout << "Start shooting..." << std::endl;
            _shootingSimulator.setConfig(_configBasedOnDifficulty[_aiComponent->getDifficulty()]);
            _shootingSimulator.tryHitting(_entityId, _targetId);
        } else {
            drawShootingLine(_directHit);
            fireProjectile(_directHit);
        }
        _projectileFired = true;
        _timePassed = 1;
    } else {
        _timePassed += dt;
        if (!_powerBar.isVisible()) {
            _powerBar.show();
            _powerBar.lockToPlayer(_entityId);
        }
        _powerBar.update(dt);

        if (_timePassed > 0.5) {
            drawShootingLine(_shootingSimulator.getMostSuccessfulShot());
            _timePassed = 0;
        }
    }
}

void AttackState::exit() {
    _shootingSimulator.cleanup();
    _powerBar.hide();
    _shootingLine.hide();
}

void AttackState::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    _projectileFired = false;
    _projectileId = -1;
}

bool AttackState::canHandle(const CollisionEvent &collisionEvent) {
    return _projectileFired && (collisionEvent.getEntity() == _projectileId || collisionEvent.getOtherEntity() == _projectileId);
}

void AttackState::shotFound(ShotTry shotTry, bool directHit) {
    _powerBar.setPower(shotTry.getPower());
    _shootingSimulator.cleanup();
    _canHitTarget = directHit;
    if (_canHitTarget)
        _directHit = shotTry;
    fireProjectile(shotTry);
}

void AttackState::fireProjectile(const ShotTry &shotTry) {
    //std::cout << "Firing projectile, angle: " <<  shotTry.getAngle() << ", power: " << shotTry.getPower() << std::endl;
    _projectileFired = true;

    auto playerComponent = _entityManager->getComponentFromEntity<PlayerComponent>(_entityId);
    Weapon *selectedWeapon = playerComponent->getSelectedWeapon();

    ProjectileBuilder projectileBuilder{*_entityManager};

    double deviation = _deviationBasedOnDifficulty[_aiComponent->getDifficulty()];
    double angle = shotTry.getAngle();
    double velocityY = shotTry.getYVelocity();
    double velocityX = shotTry.getXVelocity();
    double power = shotTry.getPower();
    if (deviation > 0) {
        angle = _random.between(angle - deviation, angle + deviation);
        double radianAngle = angle * M_PI / 180.0;
        velocityY = deviation > 0 ? -1 * std::round(cos(radianAngle) * projectileBuilder.maxVeloctiy * 100) / 100
                                  : shotTry.getYVelocity();
        velocityX = deviation > 0 ? std::round(sin(radianAngle) * projectileBuilder.maxVeloctiy * 100) / 100
                                  : shotTry.getXVelocity();
        velocityX = _targetPosition.X > _positionComponent->X ? velocityX : -velocityX;
        power = _random.between(power - deviation, power + deviation);
    }

    std::cout << "Angle: " << angle << ", power: " << shotTry.getPower() << std::endl;

    if(!hasAmmo()) return;
    _turnComponent->lowerEnergy(20);
    selectedWeapon->lowerAmmo();
    _projectileId = projectileBuilder
            .setYVelocity(velocityY)
            .setXVelocity(velocityX)
            .setPower(power)
            .setWeapon(*selectedWeapon)
            .setPlayerCollider(*_boxCollider)
            .setPlayerPostion(*_positionComponent)
            .build();
    _context->getAudioFacade().playEffect("throwing");
    _shootingLine.hide();
    _powerBar.hide();
}

bool AttackState::hasAmmo(){
    auto playerComponent = _entityManager->getComponentFromEntity<PlayerComponent>(_entityId);
    Weapon *selectedWeapon = playerComponent->getSelectedWeapon();

    for (int i = playerComponent->getAmountOFWeapons(); i > 0; i--) {
        selectedWeapon = playerComponent->getSelectedWeapon();
        if (selectedWeapon->getAmmo() > 0) break;
        playerComponent->setSelectedWeapon("next");
    }
    return selectedWeapon->getAmmo() > 0;
}

void AttackState::drawShootingLine(const ShotTry &shotTry) {
    double playerCenterX = _positionComponent->X + _boxCollider->width / 2.0;
    double playerCenterY = _positionComponent->Y + _boxCollider->height / 2.0;
    _shootingLine.setFromX(playerCenterX);
    _shootingLine.setFromY(playerCenterY);
    _shootingLine.setToX(playerCenterX + shotTry.getXVelocity());
    _shootingLine.setToY(playerCenterY + shotTry.getYVelocity());
    _shootingLine.show();
}
