#ifndef PROJECT_SWA_PROJECTILEBUILDER_H
#define PROJECT_SWA_PROJECTILEBUILDER_H

#include "../../Entities/EntityManager.h"
#include "../../Components/Collider/BoxCollider.h"
#include "../../Components/PositionComponent.h"
#include "../../../StateMachine/Misc/Weapon.h"

class ProjectileBuilder {
private:
    EntityManager *_entityManager;

    //variables
    double _xVelocity = maxVeloctiy;
    double _yVelocity = maxVeloctiy;
    double _power = 0;
    bool _isVirtual = false;
    double _playerCenterX = -1;
    double _playerCenterY = -1;
    const Weapon *_weapon = nullptr;
    const BoxCollider *_collider = nullptr;
    const PositionComponent *_position = nullptr;
public:
    // hardcoded values :/
    const int projectileWidth = 11;
    const int projectileHeight = 32;
    const int bulletSpawnOffset = 2;
    const int maxVeloctiy = 150;
    const int minVeloctiy = 10;
    const int maxPower = 50;
    const double powerDivision = 20;
    const double speedModifier = 2.5;
    const double gravityModifier = 6.0;
    const double damageOfProjectile = 25;
    const double healthOfProjectile = 10;

    explicit ProjectileBuilder(EntityManager &entityManager);

    ProjectileBuilder &setXVelocity(double xVelocity);

    ProjectileBuilder &setYVelocity(double yVelocity);

    ProjectileBuilder &setShootingAngle(double angle);

    ProjectileBuilder &setPower(double power);

    ProjectileBuilder &isVirtual(bool isVirtual);

    ProjectileBuilder &setPlayerCenterX(int playerCenterX);

    ProjectileBuilder &setPlayerCenterY(int playerCenterY);

    ProjectileBuilder &setWeapon(const Weapon &weapon);

    ProjectileBuilder &setPlayerCollider(const BoxCollider &collider);

    ProjectileBuilder &setPlayerPostion(const PositionComponent &positionComponent);

    int build();
};

#endif //PROJECT_SWA_PROJECTILEBUILDER_H
