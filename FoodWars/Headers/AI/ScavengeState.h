#ifndef PROJECT_SWA_SCAVENGE_H
#define PROJECT_SWA_SCAVENGE_H

#include "State.h"

class ScavengeState : public State {
public:
    ScavengeState() = default;
    ~ScavengeState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_SCAVENGE_H