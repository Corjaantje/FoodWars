#ifndef PROJECT_SWA_CHARACTERBUILDER_H
#define PROJECT_SWA_CHARACTERBUILDER_H


#include "DifficultyEnum.h"
#include "FactionEnum.h"
#include "../../GameECS/Entities/EntityManager.h"

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

    void buildCharacterEntity(EntityManager* entityManager);
private:
    bool _isBot = false;
    Difficulty _botDifficulty = Difficulty::EASY;

    Faction _faction = Faction::RANDOM;
};


#endif //PROJECT_SWA_CHARACTERBUILDER_H
