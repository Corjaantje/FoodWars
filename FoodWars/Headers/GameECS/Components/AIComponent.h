#ifndef PROJECT_SWA_AICOMPONENT_H
#define PROJECT_SWA_AICOMPONENT_H

#include "PlayerComponent.h"

class AIComponent : public PlayerComponent{
private:
    //int _playerID;
    int _difficulty;
public:
    explicit AIComponent(int playerID, int difficulty);
    int getDifficulty() const;
};

#endif //PROJECT_SWA_AICOMPONENT_H