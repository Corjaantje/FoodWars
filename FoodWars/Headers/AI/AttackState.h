#ifndef PROJECT_SWA_ATTACKSTATE_H
#define PROJECT_SWA_ATTACKSTATE_H

#include <unordered_map>
#include <bits/unordered_map.h>
#include "State.h"
#include "../GameECS/Components/DamageableComponent.h"
#include "ShootingSimulator2019.h"
#include "../GameECS/Systems/Misc/LineDrawer.h"
#include "../GameECS/Systems/Misc/PowerBar.h"
#include "../StateMachine/Misc/DifficultyEnum.h"

class AttackState : public State, public CollisionEventHandler {
private:
    bool _canHitTarget = false;
    ShotTry _directHit{0, 0};
    bool _projectileFired = false;
    int _projectileId = -1;
    int _targetId;
    PositionComponent _targetPosition;
    const DamageableComponent* _target;
    ShootingSimulator2019 _shootingSimulator;
    LineDrawer _shootingLine;
    PowerBar _powerBar;
    double _timePassed = 0;
    Random _random;
    std::unordered_map<Difficulty, ShootingSimulatorConfig> _configBasedOnDifficulty;
    std::unordered_map<Difficulty, double> _deviationBasedOnDifficulty;
    bool hasAmmo();
    void fireProjectile(const ShotTry &shotTry);

    void drawShootingLine(const ShotTry &shotTry);
public:
    AttackState(EntityManager &entityManager, int entityId, int targetId, const PositionComponent &targetPosition, const DamageableComponent &target, AISystem &context);

    ~AttackState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;

    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;

    void shotFound(ShotTry shotTry, bool directHit);
};


#endif //PROJECT_SWA_ATTACKSTATE_H
