#ifndef PROJECT_SWA_FLEESTATE_H
#define PROJECT_SWA_FLEESTATE_H


#include "State.h"

class FleeState : public State {
public:
    FleeState() = default;

    ~FleeState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_FLEESTATE_H