#ifndef PROJECT_SWA_CHARACTERBUILDER_H
#define PROJECT_SWA_CHARACTERBUILDER_H


#include "DifficultyEnum.h"
#include "FactionEnum.h"

class CharacterBuilder {
public:
    CharacterBuilder() = default;
    ~CharacterBuilder() = default;
public:
    bool getIsBot() const;
    const void setIsBot(const bool state);

    FACTION getFaction() const;
    const void setFaction(const FACTION faction);
private:
    bool _isBot = false;
    DIFFICULTY _botDifficulty = DIFFICULTY::EASY;

    FACTION _faction = FACTION::WHITE;
};


#endif //PROJECT_SWA_CHARACTERBUILDER_H
