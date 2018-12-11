#ifndef PROJECT_SWA_LEVELSTORAGE_H
#define PROJECT_SWA_LEVELSTORAGE_H

#include "../StateMachine/Misc/GameLevel.h"

class LevelStorage {
public:
    bool saveLevel(const GameLevel &gameLevel, const std::string &toFile);

    bool loadLevel(GameLevel &gameLevel, const std::string &file);
};

#endif //PROJECT_SWA_LEVELSTORAGE_H
