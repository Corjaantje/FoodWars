#ifndef PROJECT_SWA_LEVELMANAGER_H
#define PROJECT_SWA_LEVELMANAGER_H

#include "StateMachine/Misc/GameLevel.h"

class LevelLoader {
private:
    void spawnPlayers(GameLevel &gameLevel);
public:
    LevelLoader();

    ~LevelLoader();

    GameLevel *loadLevel(int level, GameLevel &gameLevel);

};
#endif //PROJECT_SWA_LEVELMANAGER_H
