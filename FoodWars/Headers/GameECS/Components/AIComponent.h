#ifndef PROJECT_SWA_AICOMPONENT_H
#define PROJECT_SWA_AICOMPONENT_H

#include "PlayerComponent.h"
#include "../../../Headers/AI/State.h"
#include <memory>

class AIComponent : public PlayerComponent{
private:
    int _difficulty;
    std::unique_ptr<State> _currentState;
public:
    AIComponent(int playerID, int difficulty, int entityId);

    int getDifficulty() const;

    void setCurrentState(std::unique_ptr<State> state);
    State* getCurrentState() const;
    void update(double dt);
};

#endif //PROJECT_SWA_AICOMPONENT_H