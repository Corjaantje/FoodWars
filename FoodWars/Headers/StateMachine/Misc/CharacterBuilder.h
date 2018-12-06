#ifndef PROJECT_SWA_CHARACTERBUILDER_H
#define PROJECT_SWA_CHARACTERBUILDER_H


#include "DifficultyEnum.h"
#include "FactionEnum.h"
#include "../../GameECS/Entities/EntityManager.h"
#include "GameLevel.h"

class CharacterBuilder {
public:
    CharacterBuilder() = default;
    ~CharacterBuilder() = default;
public:
    bool getIsBot() const;
    const void setIsBot(bool state);

    Faction getFaction() const;
    const void setFaction(Faction faction);

    Difficulty getDifficulty() const;
    void increaseDifficulty();
    void decreaseDifficulty();

    void buildCharacterEntity(GameLevel &gameLevel, int playerID, int spawnX, int spawnY, bool startTurn);
private:
    bool _isBot = false;
    Difficulty _botDifficulty = Difficulty::EASY;

    Faction _faction = Faction::RANDOM;
};


#endif //PROJECT_SWA_CHARACTERBUILDER_H
