#ifndef PROJECT_SWA_IDLESTATE_H
#define PROJECT_SWA_IDLESTATE_H

#include "State.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/TurnComponent.h"
#include "../GameECS/Components/AIComponent.h"

class IdleState : public State {
private:
    int _maxShootingRange = 700;
    std::string _previousState;
    int _playerCenterX = -1;
    int _playerCenterY = -1;
    int _enemyId = -1;

    int getEnemyId();
    int getClosestItem();
    double getDistanceToPoint(int target);
    int getAmountOfAmmo();
    int getEnemyHealth();
    void chooseState();

    void flee();
public:
    IdleState(EntityManager& entityManager, int entityId, std::string previousState, AISystem& context);

    ~IdleState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_IDLESTATE_H
