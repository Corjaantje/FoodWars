#ifndef PROJECT_SWA_AICOMPONENT_H
#define PROJECT_SWA_AICOMPONENT_H

#include "../../../Headers/AI/State.h"
#include "../../StateMachine/Misc/DifficultyEnum.h"
#include <memory>

class AIComponent : public Component{
private:
    int _difficulty;
    std::unique_ptr<State> _currentState;
public:
    explicit AIComponent(Difficulty difficulty);

    int getDifficulty() const;

    void setCurrentState(std::unique_ptr<State> state);
    State* getCurrentState() const;
    void update(double dt);
};

#endif //PROJECT_SWA_AICOMPONENT_H