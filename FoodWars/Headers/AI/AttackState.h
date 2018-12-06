#ifndef PROJECT_SWA_ATTACKSTATE_H
#define PROJECT_SWA_ATTACKSTATE_H

#include "State.h"

class AttackState : public State {
public:
    AttackState(EntityManager* entityManager, std::shared_ptr<AudioFacade> audioFacade, int entityId);

    ~AttackState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};


#endif //PROJECT_SWA_ATTACKSTATE_H
