#ifndef PROJECT_SWA_LEVELSTORAGE_H
#define PROJECT_SWA_LEVELSTORAGE_H

#include "../StateMachine/Misc/GameLevel.h"
#include "../../../TonicEngine/Headers/Storage/DeserializationFactory.h"

class LevelStorage {
private:
    DeserializationFactory _deserializationFactory;

    void fillFactory(DeserializationFactory &factory);
public:
    LevelStorage();
    bool saveLevel(const GameLevel &gameLevel, const std::string &toFile);

    bool loadLevel(GameLevel &gameLevel, const std::string &file);
};

#endif //PROJECT_SWA_LEVELSTORAGE_H
