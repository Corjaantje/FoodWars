#ifndef PROJECT_SWA_IDLESTATE_H
#define PROJECT_SWA_IDLESTATE_H

#include "State.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/TurnComponent.h"
#include "../GameECS/Components/AIComponent.h"

class IdleState : public State {
public:
    IdleState(EntityManager& entityManager, int entityId, AISystem& context);

    ~IdleState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_IDLESTATE_H
