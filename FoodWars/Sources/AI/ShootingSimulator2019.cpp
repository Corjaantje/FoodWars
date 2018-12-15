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
    //generateProjectile(ShotTry{_minAngle, _minPower});
    //generateProjectile(ShotTry{_minAngle, _minPower});
    generateProjectile(ShotTry{_maxAngle, _maxPower});
}

int ShootingSimulator2019::generateProjectile(ShotTry shotTry) {
    int projectileWidth = 11;
    int projectileHeight = 32;

    //double velocityX = _target->X > _fromPosition->X ? initVelocity : -initVelocity;
    double radianAngle = shotTry.getAngle() * M_PI / 180.0;
    double power = shotTry.getPower();
    double velocityY = -1 * std::round(cos(radianAngle) * 150 * 100) / 100;
    double velocityX = std::round(sin(radianAngle) * 150 * 100) / 100;
    velocityX = _target->X > _fromPosition->X ? velocityX : -velocityX;

    std::cout << "Angle: " << shotTry.getAngle() << ", power: " << shotTry.getAngle() << std::endl;
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

    std::cout << "Carrot spawn position: " << posX << ", " << posY << std::endl;
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
    //calculate score of projectile
    auto collisionPosition = _entityManager->getComponentFromEntity<PositionComponent>(otherEntity);
    shotTry.setScore(100);

    /*if (shotTry.getPower() + _powerIncrease <= _maxPower)
        generateProjectile(ShotTry{shotTry.getAngle(), shotTry.getPower() + _powerIncrease});
    if (shotTry.getAngle() + _angleIncrease <= _maxAngle)
        generateProjectile(ShotTry{shotTry.getAngle() + _angleIncrease, shotTry.getPower()});*/
}

bool ShootingSimulator2019::canHandle(const CollisionEvent &collisionEvent) {
    return (_shootingTries.find(collisionEvent.getEntity()) != _shootingTries.end() &&
            _shootingTries.find(collisionEvent.getOtherEntity()) == _shootingTries.end()) ||
           (_shootingTries.find(collisionEvent.getOtherEntity()) != _shootingTries.end() &&
            _shootingTries.find(collisionEvent.getEntity()) == _shootingTries.end());
}