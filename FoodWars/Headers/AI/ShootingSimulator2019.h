#ifndef PROJECT_SWA_SHOOTINGSIMULATOR2019_H
#define PROJECT_SWA_SHOOTINGSIMULATOR2019_H

#include "../GameECS/Events/CollisionEventHandler.h"
#include "../GameECS/Components/PositionComponent.h"
#include "../GameECS/Entities/EntityManager.h"
#include "ShotTry.h"
#include "../GameECS/Components/Collider/BoxCollider.h"
#include "../GameECS/Systems/Misc/ProjectileBuilder.h"
#include "ShootingSimulatorConfig.h"
#include "../../../TonicEngine/Headers/General/Random.h"

class ShootingSimulator2019 : public CollisionEventHandler {
private:
    EntityManager *_entityManager;
    ProjectileBuilder _projectileBuilder;
    std::unordered_map<int, ShotTry> _shootingTries;
    std::vector<int> _projectileIds;
    int _playerId;
    int _targetId;
    ShootingSimulatorConfig _config;
    Random _random;

    int generateProjectile(ShotTry shotTry);

    const PositionComponent *_target;
    const PositionComponent *_playerPosition;
    const BoxCollider *_playerCollider;
    PositionComponent _centerPlayerPosition;

    ShotTry mostSuccessfulShot = ShotTry{90, _config.getMaxPower()};
    std::function<void(const ShotTry &, bool)> _onShotFoundFunc;
public:
    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;

    ShootingSimulator2019(IObservable<CollisionEvent> &collisionEventObservable, EntityManager &entityManager,
                          const std::function<void(const ShotTry &, bool)> &onShotFoundFunc);

    ~ShootingSimulator2019();

    void tryHitting(int playerId, int targetId);

    void setConfig(const ShootingSimulatorConfig &config);

    void cleanup();

    ShotTry getMostSuccessfulShot() const;
};

#endif //PROJECT_SWA_SHOOTINGSIMULATOR2019_H