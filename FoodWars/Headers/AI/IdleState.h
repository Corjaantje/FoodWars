#ifndef PROJECT_SWA_IDLESTATE_H
#define PROJECT_SWA_IDLESTATE_H

#include "State.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/TurnComponent.h"
#include "../GameECS/Components/AIComponent.h"

class IdleState : public State {
private:
    std::string _previousState;

    int getClosestItem();
    double getDistanceToEnemy();
    int getAmountOfAmmo();
    int getEnemyHealth();
    void chooseState();
public:
    IdleState(EntityManager& entityManager, int entityId, std::string previousState, AISystem& context);

    ~IdleState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_IDLESTATE_H
