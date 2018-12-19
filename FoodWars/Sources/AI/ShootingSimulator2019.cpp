#include <cmath>
#include "../../Headers/AI/ShootingSimulator2019.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../Headers/GameECS/Components/ItemComponent.h"

ShootingSimulator2019::ShootingSimulator2019(IObservable<CollisionEvent> &collisionEventObservable,
                                             EntityManager &entityManager,
                                             const std::function<void(const ShotTry &, bool)> &onShotFoundFunc) :
        CollisionEventHandler(collisionEventObservable),
        _config{},
        _projectileBuilder{entityManager},
        _onShotFoundFunc{onShotFoundFunc},
        _entityManager{&entityManager},
        _projectileIds{},
        _target{nullptr} {

}

void ShootingSimulator2019::tryHitting(int playerId, int targetId) {
    _playerId = playerId;
    _targetId = targetId;
    _target = _entityManager->getComponentFromEntity<PositionComponent>(targetId);
    _playerPosition = _entityManager->getComponentFromEntity<PositionComponent>(playerId);
    _playerCollider = _entityManager->getComponentFromEntity<BoxCollider>(playerId);
    _centerPlayerPosition = PositionComponent{(int) std::round(_playerPosition->X + _playerCollider->width / 2.0),
                                              (int) std::round(_playerPosition->Y + _playerCollider->height / 2.0)};

    double currentAngle = _config.getMinAngle();
    while (currentAngle + _config.getAngleIncrease() <= _config.getMaxAngle()) {
        generateProjectile(ShotTry{currentAngle, _config.getMinPower()});
        generateProjectile(ShotTry{currentAngle, _config.getMaxPower()});
        currentAngle += _config.getAngleIncrease();
    }
}

int ShootingSimulator2019::generateProjectile(ShotTry shotTry) {
    double radianAngle = shotTry.getAngle() * M_PI / 180.0;
    double velocityY = -1 * std::round(cos(radianAngle) * _projectileBuilder.maxVeloctiy * 100) / 100;
    double velocityX = std::round(sin(radianAngle) * _projectileBuilder.maxVeloctiy * 100) / 100;
    velocityX = _target->X > _centerPlayerPosition.X ? velocityX : -velocityX;
    //std::cout << "Trying angle: " << shotTry.getAngle() << ", power: " << shotTry.getPower() << std::endl;
    shotTry.setYVeloctity(velocityY);
    shotTry.setXVeloctity(velocityX);
    int projectile = _projectileBuilder
            .setPower(shotTry.getPower())
            .setXVelocity(velocityX)
            .setYVelocity(velocityY)
            .isVirtual(true)
            .setPlayerPostion(*_playerPosition)
            .setPlayerCollider(*_playerCollider)
            .build();

    _shootingTries[projectile] = shotTry;
    _projectileIds.push_back(projectile);
    return projectile;
}

void ShootingSimulator2019::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    auto projectile = _shootingTries.find(collisionEvent.getEntity());
    int otherEntity = collisionEvent.getOtherEntity();
    if (projectile == _shootingTries.end()) {
        projectile = _shootingTries.find(collisionEvent.getOtherEntity());
        otherEntity = collisionEvent.getEntity();
        if (projectile == _shootingTries.end()) return;
    }
    int projectileId = projectile->first;
    _entityManager->getComponentFromEntity<DamageableComponent>(projectileId)->destroy();
    ShotTry shotTry = projectile->second;
    _shootingTries.erase(projectileId);

    if (shotTry.getScore() < 0) { //hit has not been processed yet
        if (otherEntity == _targetId) {
            shotTry.setScore(0);
            mostSuccessfulShot = shotTry;
            _onShotFoundFunc(shotTry, true);
        } else if (mostSuccessfulShot.getScore() !=
                   0) { //no direct hit on target so calculate score, the lower the better
            auto collisionPosition = _entityManager->getComponentFromEntity<PositionComponent>(otherEntity);
            shotTry.setScore(std::abs(collisionPosition->X - _target->X) + std::abs(collisionPosition->Y - _target->Y));
            if (mostSuccessfulShot.getScore() < 0 || shotTry.getScore() < mostSuccessfulShot.getScore()) {
                mostSuccessfulShot = shotTry;
            }
            if (shotTry.getPower() + _config.getPowerIncrease() < _config.getMaxPower()) {
                generateProjectile(ShotTry{shotTry.getAngle(), shotTry.getPower() + _config.getPowerIncrease()});
            } else if (_shootingTries.empty())
                _onShotFoundFunc(mostSuccessfulShot, false);
        }
    }
}

bool ShootingSimulator2019::canHandle(const CollisionEvent &collisionEvent) {
    bool entityIsProjectile =
            std::find(_projectileIds.begin(), _projectileIds.end(), collisionEvent.getEntity()) != _projectileIds.end();
    bool otherEntityIsProjectile =
            std::find(_projectileIds.begin(), _projectileIds.end(), collisionEvent.getOtherEntity()) !=
            _projectileIds.end();
    return (entityIsProjectile && !otherEntityIsProjectile &&
            !_entityManager->getComponentFromEntity<ItemComponent>(collisionEvent.getOtherEntity())) ||
           (!entityIsProjectile && otherEntityIsProjectile &&
            !_entityManager->getComponentFromEntity<ItemComponent>(collisionEvent.getEntity()));
    //true when a projectile collides with something thats not a projectile
}

void ShootingSimulator2019::cleanup() {
    mostSuccessfulShot = ShotTry{90, _config.getMaxPower()};
    for (const auto shot: _shootingTries) {
        _entityManager->removeEntity(shot.first);
    }
    _shootingTries.clear();
    _projectileIds.clear();
}

ShootingSimulator2019::~ShootingSimulator2019() {
    if (!_shootingTries.empty())
        this->cleanup();
}

ShotTry ShootingSimulator2019::getMostSuccessfulShot() const {
    return mostSuccessfulShot;
}

void ShootingSimulator2019::setConfig(const ShootingSimulatorConfig &config) {
    _config = config;
}