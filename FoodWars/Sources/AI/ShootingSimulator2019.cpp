#include <cmath>
#include "../../Headers/AI/ShootingSimulator2019.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"

ShootingSimulator2019::ShootingSimulator2019(IObservable<CollisionEvent> &collisionEventObservable,
                                             EntityManager &entityManager,
                                             const std::function<void(const ShotTry &, bool)> &onShotFoundFunc) :
        CollisionEventHandler(collisionEventObservable),
        _projectileBuilder{entityManager},
        _onShotFoundFunc{onShotFoundFunc},
        _entityManager{&entityManager},
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

    _currentProjectiles = 0;
    _maxProjectiles =
            static_cast<int>(((_maxAngle - _minAngle) / _angleIncrease) * ((_maxPower - _minPower) / _powerIncrease));

    double currentAngle = _minAngle;
    while (currentAngle + _angleIncrease <= _maxAngle) {
        generateProjectile(ShotTry{currentAngle, _minPower});
        currentAngle += _angleIncrease;
    }
}

int ShootingSimulator2019::generateProjectile(ShotTry shotTry) {
    _currentProjectiles++;
    //std::cout << "Current projectiles: " << _currentProjectiles << ", max: " << _maxProjectiles << std::endl;
    int projectileWidth = 11;
    int projectileHeight = 32;

    //double velocityX = _target->X > _centerPlayerPosition->X ? initVelocity : -initVelocity;
    double radianAngle = shotTry.getAngle() * M_PI / 180.0;
    double power = shotTry.getPower();
    double velocityY = -1 * std::round(cos(radianAngle) * _projectileBuilder.maxVeloctiy * 100) / 100;
    double velocityX = std::round(sin(radianAngle) * _projectileBuilder.maxVeloctiy * 100) / 100;
    velocityX = _target->X > _centerPlayerPosition.X ? velocityX : -velocityX;
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

    //std::cout << "Angle: " << shotTry.getAngle() << ", power: " << shotTry.getPower() << std::endl;
    //std::cout << "velocityX: " << velocityX << ", velocityY: " << velocityY << ", power: " << power << std::endl;
    /*int posX = _centerPlayerPosition.X;
    int posY = _centerPlayerPosition.Y;

    // Checks for shooting down
    if (velocityX > 0 && velocityY > 70) posY = _centerPlayerPosition.Y + (_playerCollider->height / 2) + 1;
    else if (velocityX <= 0 && velocityY > 70) posY = _centerPlayerPosition.Y + (_playerCollider->height / 2) + 1;
        // Checks for shooting up
    else if (velocityX > 0 && velocityY <= -70) posY = _centerPlayerPosition.Y - (_playerCollider->height / 2) - 1;
    else if (velocityX <= 0 && velocityY <= -70) posY = _centerPlayerPosition.Y - (_playerCollider->height / 2) - 1;
        // Remaining default checks
    else if (velocityX > 0) posX = _centerPlayerPosition.X + (_playerCollider->width / 2) + 1;
    else if (velocityX <= 0) posX = _centerPlayerPosition.X - (_playerCollider->width / 2) - (projectileWidth - 1);
    if (velocityY < 0) posY -= projectileHeight + 1;

    //std::cout << "Carrot spawn position: " << posX << ", " << posY << std::endl;
    const double speedModifier = 2.5;

    int projectile = _entityManager->createEntity();
    _entityManager->addComponentToEntity<DrawableComponent>(projectile,
                                                            std::make_unique<ShapeRectangle>(projectileWidth,
                                                                                             projectileHeight,
                                                                                             posX, posY,
                                                                                             Colour{255, 0, 255, 100}));
    _entityManager->addComponentToEntity<PositionComponent>(projectile, posX, posY);
    _entityManager->addComponentToEntity<BoxCollider>(projectile, projectileWidth, projectileHeight, true);
    _entityManager->addComponentToEntity<DamageableComponent>(projectile, 10);
    _entityManager->addComponentToEntity<GravityComponent>(projectile, 6 * speedModifier);
    _entityManager->addComponentToEntity<MoveComponent>(projectile, (power / 20) * velocityX * speedModifier,
                                                        (power / 20) * velocityY * speedModifier);*/
    _shootingTries[projectile] = shotTry;
    return projectile;
}

void ShootingSimulator2019::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    auto projectile = _shootingTries.find(collisionEvent.getEntity());
    int otherEntity = collisionEvent.getOtherEntity();
    if (projectile == _shootingTries.end()) {
        projectile = _shootingTries.find(collisionEvent.getOtherEntity());
        otherEntity = collisionEvent.getEntity();
    }
    int projectileId = projectile->first;
    _entityManager->getComponentFromEntity<DamageableComponent>(projectileId)->destroy();
    ShotTry &shotTry = projectile->second;
    if (shotTry.getScore() < 0) { //hit has not been processed yet
        if (!mostSuccessfulShot) {
            mostSuccessfulShot = &shotTry;
        }
        if (otherEntity == _targetId) {
            shotTry.setScore(0);
            mostSuccessfulShot = &shotTry;
            _onShotFoundFunc(shotTry, true);
        } else if (mostSuccessfulShot->getScore() !=
                   0) { //no direct hit on target so calculate score, the lower the better
            auto collisionPosition = _entityManager->getComponentFromEntity<PositionComponent>(otherEntity);
            shotTry.setScore(std::abs(collisionPosition->X - _target->X) + std::abs(collisionPosition->Y - _target->Y));
            if (shotTry.getScore() < mostSuccessfulShot->getScore()) {
                mostSuccessfulShot = &shotTry;
            }

            if (shotTry.getPower() + _powerIncrease <= _maxPower) {
                generateProjectile(ShotTry{shotTry.getAngle(), shotTry.getPower() + _powerIncrease});
            } else if (_currentProjectiles >= _maxProjectiles)
                _onShotFoundFunc(*mostSuccessfulShot, false);
        }
    }
}

bool ShootingSimulator2019::canHandle(const CollisionEvent &collisionEvent) {
    return (_shootingTries.find(collisionEvent.getEntity()) != _shootingTries.end() &&
            _shootingTries.find(collisionEvent.getOtherEntity()) == _shootingTries.end()) ||
           (_shootingTries.find(collisionEvent.getOtherEntity()) != _shootingTries.end() &&
            _shootingTries.find(collisionEvent.getEntity()) ==
            _shootingTries.end()); //true when a projectile collides with something thats not a projectile
}

void ShootingSimulator2019::cleanup() {
    _currentProjectiles = 0;
    _maxProjectiles = 0;
    for (const auto shot: _shootingTries) {
        _entityManager->removeEntity(shot.first);
    }
    _shootingTries.clear();
}

ShootingSimulator2019::~ShootingSimulator2019() {
    if (_currentProjectiles > 0)
        this->cleanup();
}
