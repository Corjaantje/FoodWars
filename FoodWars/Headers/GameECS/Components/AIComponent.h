#ifndef PROJECT_SWA_AICOMPONENT_H
#define PROJECT_SWA_AICOMPONENT_H

#include "PlayerComponent.h"
#include "../../AI/State.h"
#include <memory>

class AIComponent : public PlayerComponent{
private:
    //int _playerID;
    int _difficulty;
    std::unique_ptr<State> _currentState = nullptr;
public:
    explicit AIComponent(int playerID, int difficulty);

    int getDifficulty() const;

    void setCurrentState(std::unique_ptr<State> state);
    void update(double dt);
};

#endif //PROJECT_SWA_AICOMPONENT_H