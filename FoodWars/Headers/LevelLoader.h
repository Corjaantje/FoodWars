#ifndef PROJECT_SWA_LEVELMANAGER_H
#define PROJECT_SWA_LEVELMANAGER_H

#include "StateMachine/Misc/GameLevel.h"
#include "StateMachine/Misc/CharacterBuilder.h"

const std::string DEFAULT_XMLPATH = "./Assets/Levels/";
class LevelLoader {
private:
    void spawnPlayers(GameLevel &gameLevel, CharacterBuilder playerOne, CharacterBuilder playerTwo);
public:
    LevelLoader();

    ~LevelLoader();

    GameLevel *loadLevel(std::string levelPath, GameLevel &gameLevel, CharacterBuilder playerOne, CharacterBuilder playerTwo);

    void replayLastLevel(GameLevel &gameLevel);
    void playNextLevel(GameLevel &gamelevel);
    std::string getLevelIdentifier() const;
private:
    std::string _lastPlayedLevelPath;
    CharacterBuilder _lastPlayedCharacterOne;
    CharacterBuilder _lastPlayedCharacterTwo;
};
#endif //PROJECT_SWA_LEVELMANAGER_H
