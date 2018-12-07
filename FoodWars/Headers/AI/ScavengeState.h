#ifndef PROJECT_SWA_SCAVENGE_H
#define PROJECT_SWA_SCAVENGE_H

#include "State.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/TurnComponent.h"

class ScavengeState : public State, public CollisionEventHandler {
public:
    ScavengeState(EntityManager& entityManager, int entityId, AISystem& context);
    ~ScavengeState() override = default;

    void enter() override;

    void handleCollisionEvent(const CollisionEvent &collisionEvent) override;

    bool canHandle(const CollisionEvent &collisionEvent) override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_SCAVENGE_H