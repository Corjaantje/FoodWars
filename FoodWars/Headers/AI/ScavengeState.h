#ifndef PROJECT_SWA_SCAVENGE_H
#define PROJECT_SWA_SCAVENGE_H

#include "State.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/TurnComponent.h"

class ScavengeState : public State {
private:
    MoveComponent* _moveComponent;
    TurnComponent* _turnComponent;
public:
    ScavengeState(MoveComponent* moveComponent, TurnComponent* turnComponent);
    ~ScavengeState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_SCAVENGE_H