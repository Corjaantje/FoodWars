#include <cmath>
#include "../../Headers/AI/ShootingSimulator2019.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"

ShootingSimulator2019::ShootingSimulator2019(IObservable<CollisionEvent> &collisionEventObservable,
                                             EntityManager &entityManager) :
        CollisionEventHandler(collisionEventObservable),
        _entityManager{&entityManager},
        _target{nullptr} {

}

void ShootingSimulator2019::tryHitting(const PositionComponent &target, const PositionComponent &fromPosition) {
    _target = &target;
    _fromPosition = &fromPosition;
    _currentPower = _minPower;
    generateProjectile(_minPower, _minYVelocity);
    generateProjectile(_minPower, _minYVelocity);
}

int ShootingSimulator2019::generateProjectile(double power, double yVelocity) {
    int projectileWidth = 11;
    int projectileHeight = 32;
    int initVelocity = 250;
    double velocityX = _target->X > _fromPosition->X ? initVelocity : -initVelocity;
    double velocityY = yVelocity;

    // shooting in a circle
    double totalLength = sqrt(velocityX * velocityX + velocityY * velocityY);
    double length = totalLength > 150 ? 150 : totalLength;
    double scale = length / totalLength;

    velocityX *= scale;
    velocityY *= scale;

    std::cout << "velocityX: " << velocityX << ", velocityY: " << velocityY << ", power: " << power << std::endl;
    int posX = _fromPosition->X;
    int posY = _fromPosition->Y;
    // Checks for shooting down
    if (velocityX > 0 && velocityY > 70) posY = _fromPosition->Y + 50;
    else if (velocityX <= 0 && velocityY > 70) posY = _fromPosition->Y + 50;
        // Checks for shooting up
    else if (velocityX > 0 && velocityY <= -70) posY = _fromPosition->Y - 50;
    else if (velocityX <= 0 && velocityY <= -70) posY = _fromPosition->Y - 50;
    // Remaining default checks
    if (velocityY < 0) posY -= projectileHeight + 1;

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
                                                        (power / 20) * velocityY * speedModifier);
    _shootingTries[projectile] = ShotTry{velocityX, velocityY, power};
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

    //calculate score of projectile
    auto collisionPosition = _entityManager->getComponentFromEntity<PositionComponent>(otherEntity);
    projectile->second.setScore(100);

    if (_currentPower + _powerIncrease <= _maxPower)
        generateProjectile(_currentPower + _powerIncrease, _currentYVelocity);
    if (_currentYVelocity + _yVelocityIncrease >= _maxYVelocity) {
        generateProjectile(_currentPower, _currentYVelocity + _yVelocityIncrease);
        _currentYVelocity -= _yVelocityIncrease;
    }
    if (_currentPower + _powerIncrease <= _maxPower)
        _currentPower += _powerIncrease;
}

bool ShootingSimulator2019::canHandle(const CollisionEvent &collisionEvent) {
    return (_shootingTries.find(collisionEvent.getEntity()) != _shootingTries.end() &&
            _shootingTries.find(collisionEvent.getOtherEntity()) == _shootingTries.end()) ||
           (_shootingTries.find(collisionEvent.getOtherEntity()) != _shootingTries.end() &&
            _shootingTries.find(collisionEvent.getEntity()) == _shootingTries.end());
}