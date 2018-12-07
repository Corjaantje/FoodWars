#ifndef PROJECT_SWA_LEVELMANAGER_H
#define PROJECT_SWA_LEVELMANAGER_H

#include "StateMachine/Misc/GameLevel.h"
#include "StateMachine/Misc/CharacterBuilder.h"

class LevelLoader {
private:
    void spawnPlayers(GameLevel &gameLevel, CharacterBuilder playerOne, CharacterBuilder playerTwo);
public:
    LevelLoader();

    ~LevelLoader();

    GameLevel *loadLevel(int level, GameLevel &gameLevel, CharacterBuilder playerOne, CharacterBuilder playerTwo);

    void replayLastLevel(GameLevel &gameLevel);
private:
    int _lastPlayedLevel;
    CharacterBuilder _lastPlayedCharacterOne;
    CharacterBuilder _lastPlayedCharacterTwo;
};
#endif //PROJECT_SWA_LEVELMANAGER_H
