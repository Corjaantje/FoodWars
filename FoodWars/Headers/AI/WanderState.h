#ifndef PROJECT_SWA_SCAVENGE_H
#define PROJECT_SWA_SCAVENGE_H

#include "State.h"
#include "../GameECS/Components/TurnComponent.h"
#include "../GameECS/Components/DamageableComponent.h"

class WanderState : public State, public CollisionEventHandler {
private:
    const int _walkingEnergyCostPerSecond = 20;
    PositionComponent _targetPosition;
    const DamageableComponent* _target;

    void walkLeft(double dt);
    void walkRight(double dt);
    void moveToTarget(double dt);
public:
    WanderState(EntityManager& entityManager, int entityId, const PositionComponent &targetPosition, const DamageableComponent &target, AISystem& context);
    ~WanderState() override = default;

    void enter() override;

    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;

    bool canJumpOverObstruction(int obstructionId);

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_SCAVENGE_H