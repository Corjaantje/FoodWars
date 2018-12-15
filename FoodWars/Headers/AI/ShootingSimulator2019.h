#ifndef PROJECT_SWA_SHOOTINGSIMULATOR2019_H
#define PROJECT_SWA_SHOOTINGSIMULATOR2019_H

#include "../GameECS/Events/CollisionEventHandler.h"
#include "../GameECS/Components/PositionComponent.h"
#include "../GameECS/Entities/EntityManager.h"
#include "ShotTry.h"
#include "../GameECS/Components/Collider/BoxCollider.h"
#include "../GameECS/Systems/Misc/ProjectileBuilder.h"

class ShootingSimulator2019 : public CollisionEventHandler {
private:
    EntityManager *_entityManager;
    ProjectileBuilder _projectileBuilder;
    int _currentProjectiles = 0;
    int _maxProjectiles = 0;
    std::unordered_map<int, ShotTry> _shootingTries;
    int _playerId;
    int _targetId;

    double _powerIncrease = 8;
    double _minPower = 10;
    double _maxPower = 50;

    double _minAngle = 0;
    double _maxAngle = 135;
    double _angleIncrease = 10;

    int generateProjectile(ShotTry shotTry);

    const PositionComponent *_target;
    const PositionComponent *_playerPosition;
    const BoxCollider *_playerCollider;
    PositionComponent _centerPlayerPosition;

    ShotTry *mostSuccessfulShot = nullptr;
    std::function<void(const ShotTry &, bool)> _onShotFoundFunc;
public:
    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;

    ShootingSimulator2019(IObservable<CollisionEvent> &collisionEventObservable, EntityManager &entityManager,
                          const std::function<void(const ShotTry &, bool)> &onShotFoundFunc);

    ~ShootingSimulator2019();

    void tryHitting(int playerId, int targetId);

    void cleanup();
};

#endif //PROJECT_SWA_SHOOTINGSIMULATOR2019_H