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
    //switch to idle if there is no reason to be in attack state
    if(!_turnComponent->isMyTurn()
       || _turnComponent->getRemainingTime() <= 0
       || _turnComponent->getEnergy() < 20.0
       || !hasAmmo()
       || !_target
       || !_target->isAlive()) {
        _aiComponent->setCurrentState(std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
        return;
    }

    if (!_projectileFired) {
        if (!_canHitTarget) { // no direct hit on target is known so search for shot
            _shootingSimulator.setConfig(_configBasedOnDifficulty[_aiComponent->getDifficulty()]);
            _shootingSimulator.tryHitting(_entityId, _targetId);
        } else {
            // can hit target so set _fireprojectile true
            drawShootingLine(_shot);
            _fireProjectile = true;
        }
        _projectileFired = true;
        _timePassed = 1;
    } else {
        //update powerbar
        _timePassed += dt;
        if (!_powerBar.isVisible()) {
            _powerBar.show();
            _powerBar.lockToPlayer(_entityId);
        }
        _powerBar.update(dt);

        //update shootingline
        if (_timePassed > 0.2) {
            if (_fireProjectile)
                drawShootingLine(_shot);
            else
                drawShootingLine(_shootingSimulator.getMostSuccessfulShot());
            _timePassed = 0;
        }

        //shoot if possible
        if (_fireProjectile && std::abs(_powerBar.getPower() - _shot.getPower()) < 3) {
            _powerBar.setPower(static_cast<int>(_shot.getPower()));
            drawShootingLine(_shot);
            fireProjectile(_shot);
            _fireProjectile = false;
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
    drawShootingLine(_shot);
    _shot = shotTry;
    _fireProjectile = true;
    _shootingSimulator.cleanup();
    _canHitTarget = directHit;
}

void AttackState::fireProjectile(const ShotTry &shotTry) {
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
        std::cout << "Deviation: " << deviation << std::endl;
        power = _random.between(power - deviation, power + deviation);
        std::cout << "New power: " << power << std::endl;
        if (power > projectileBuilder.maxPower) power = projectileBuilder.maxPower;
    }

    if(!hasAmmo()) return;
    _turnComponent->lowerEnergy(20);
    selectedWeapon->lowerAmmo();

    std::cout << "Firing projectile, angle: " << angle << ", power: " << power << std::endl;

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
    _timePassed = 1;
}

bool AttackState::hasAmmo() {
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
