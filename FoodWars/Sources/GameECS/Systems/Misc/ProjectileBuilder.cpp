#include <cmath>
#include "../../../../Headers/GameECS/Systems/Misc/ProjectileBuilder.h"
#include "../../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"

ProjectileBuilder::ProjectileBuilder(EntityManager &entityManager) : _entityManager{&entityManager} {

}

ProjectileBuilder &ProjectileBuilder::setXVelocity(double xVelocity) {
    _xVelocity = xVelocity;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setYVelocity(double yVelocity) {
    _yVelocity = yVelocity;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setShootingAngle(double angle) {
    double radianAngle = angle * M_PI / 180.0;
    _yVelocity = -1 * std::round(cos(radianAngle) * maxVeloctiy * 100) / 100;
    _xVelocity = std::round(sin(radianAngle) * maxVeloctiy * 100) / 100;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setPower(double power) {
    _power = power;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::isVirtual(bool isVirtual) {
    _isVirtual = isVirtual;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setPlayerCenterX(int playerCenterX) {
    _playerCenterX = playerCenterX;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setPlayerCenterY(int playerCenterY) {
    _playerCenterY = playerCenterY;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setWeapon(const Weapon &weapon) {
    _weapon = &weapon;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setPlayerCollider(const BoxCollider &collider) {
    _collider = &collider;
    return *this;
}

ProjectileBuilder &ProjectileBuilder::setPlayerPostion(const PositionComponent &positionComponent) {
    _position = &positionComponent;
    return *this;
}

int ProjectileBuilder::build() {
    int projectileId = _entityManager->createEntity();
    if (_playerCenterY < 0 || _playerCenterX < 0) {
        _playerCenterY = _position->Y + _collider->height / 2.0;
        _playerCenterX = _position->X + _collider->width / 2.0;
    }
    double posX = _playerCenterX;
    double posY = _playerCenterY;
    // Check for shooting down
    if (_yVelocity > minVeloctiy) posY = _playerCenterY + (_collider->height / 2.0) + bulletSpawnOffset;
        // Checks for shooting up
    else if (_yVelocity <= -minVeloctiy) posY = _playerCenterY - (_collider->height / 2.0) - bulletSpawnOffset;
    // Remaining default checks
    if (_xVelocity >= minVeloctiy) posX = _playerCenterX + (_collider->width / 2.0) + bulletSpawnOffset;
    else if (_xVelocity <= minVeloctiy)
        posX = _playerCenterX - (_collider->width / 2.0) - projectileWidth - bulletSpawnOffset;
    if (_yVelocity < 0) posY -= projectileHeight + bulletSpawnOffset;

    std::cout << "VelocityX: " << _xVelocity << ", VelocityY: " << _yVelocity << ", power: " << _power << std::endl;

    if (!_isVirtual)
        _entityManager->addComponentToEntity<DrawableComponent>(projectileId,
                                                                std::make_unique<ShapeSprite>(projectileWidth,
                                                                                              projectileHeight,
                                                                                              posX, posY,
                                                                                              _weapon->getImage()));
    else
        _entityManager->addComponentToEntity<DrawableComponent>(projectileId,
                                                                std::make_unique<ShapeRectangle>(projectileWidth,
                                                                                                 projectileHeight,
                                                                                                 posX, posY,
                                                                                                 Colour{255, 0, 255,
                                                                                                        100}));
    _entityManager->addComponentToEntity<PositionComponent>(projectileId, posX, posY);
    _entityManager->addComponentToEntity<BoxCollider>(projectileId, projectileWidth, projectileHeight, _isVirtual);
    if (_weapon)
        _entityManager->addComponentToEntity<DamagingComponent>(projectileId, damageOfProjectile,
                                                                _weapon->getFaction());
    else
        _entityManager->addComponentToEntity<DamagingComponent>(projectileId, damageOfProjectile);
    _entityManager->addComponentToEntity<DamageableComponent>(projectileId, healthOfProjectile);
    _entityManager->addComponentToEntity<GravityComponent>(projectileId, gravityModifier * speedModifier);
    _entityManager->addComponentToEntity<MoveComponent>(projectileId,
                                                        (_power / powerDivision) * _xVelocity * speedModifier,
                                                        (_power / powerDivision) * _yVelocity * speedModifier);
    return projectileId;
}