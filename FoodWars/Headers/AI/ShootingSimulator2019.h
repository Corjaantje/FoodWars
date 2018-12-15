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

    double _powerIncrease = 40;
    double _minPower = 10;
    double _maxPower = 50;

    double _minAngle = 0;
    double _maxAngle = 90;
    double _angleIncrease = 90;

    int generateProjectile(ShotTry shotTry);

    const PositionComponent *_target;
    const PositionComponent *_fromPosition;
public:
    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;

    ShootingSimulator2019(IObservable<CollisionEvent> &collisionEventObservable, EntityManager &entityManager);

    void tryHitting(const PositionComponent &positionComponent, const PositionComponent &fromPosition);

};

#endif //PROJECT_SWA_SHOOTINGSIMULATOR2019_H
