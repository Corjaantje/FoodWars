#ifndef PROJECT_SWA_SHOOTINGSIMULATOR2019_H
#define PROJECT_SWA_SHOOTINGSIMULATOR2019_H

#include "../GameECS/Events/CollisionEventHandler.h"
#include "../GameECS/Components/PositionComponent.h"
#include "../GameECS/Entities/EntityManager.h"
#include "ShotTry.h"

class ShootingSimulator2019 : public CollisionEventHandler {
private:
    EntityManager *_entityManager;
    std::vector<int> _projectileIds;
    std::unordered_map<int, ShotTry> _shootingTries;

    int _powerIncrease = 2;
    int _minPower = 10;
    int _maxPower = 50;
    int _currentPower = _minPower;

    int _minYVelocity = 0;
    int _maxYVelocity = -150;
    int _currentYVelocity = _minYVelocity;
    int _yVelocityIncrease = 10;

    int generateProjectile(double power, double yVelocity);

    const PositionComponent *_target;
    const PositionComponent *_fromPosition;
public:
    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;

    ShootingSimulator2019(IObservable<CollisionEvent> &collisionEventObservable, EntityManager &entityManager);

    void tryHitting(const PositionComponent &positionComponent, const PositionComponent &fromPosition);

};

#endif //PROJECT_SWA_SHOOTINGSIMULATOR2019_H
