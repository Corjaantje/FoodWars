#ifndef PROJECT_SWA_ATTACKSTATE_H
#define PROJECT_SWA_ATTACKSTATE_H

#include "State.h"
#include "../GameECS/Components/DamageableComponent.h"

class AttackState : public State, public CollisionEventHandler {
private:
    bool _projectileFired = false;
    int _projectileId = -1;
    PositionComponent _targetPosition;
    const DamageableComponent* _target;
public:
    AttackState(EntityManager& entityManager, int entityId, const PositionComponent& targetPosition, const DamageableComponent& target, AISystem& context);

    ~AttackState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;

    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;
};


#endif //PROJECT_SWA_ATTACKSTATE_H
