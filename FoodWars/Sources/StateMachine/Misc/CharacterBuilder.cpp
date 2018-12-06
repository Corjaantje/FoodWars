#include "../../../Headers/StateMachine/Misc/CharacterBuilder.h"

bool CharacterBuilder::getIsBot() const {
    return _isBot;
}

const void CharacterBuilder::setIsBot(bool state) {
    _isBot = state;
}

Faction CharacterBuilder::getFaction() const {
    return _faction;
}

const void CharacterBuilder::setFaction(Faction faction) {
    _faction = faction;
}

Difficulty CharacterBuilder::getDifficulty() const {
    return _botDifficulty;
}

void CharacterBuilder::increaseDifficulty() {
    _botDifficulty = static_cast<Difficulty>((_botDifficulty + 1) % (3));
}

void CharacterBuilder::decreaseDifficulty() {
    if(_botDifficulty - 1 < 0){
        _botDifficulty = static_cast<Difficulty>(2);
    }
    else{
        _botDifficulty = static_cast<Difficulty>(_botDifficulty - 1);

    }
}