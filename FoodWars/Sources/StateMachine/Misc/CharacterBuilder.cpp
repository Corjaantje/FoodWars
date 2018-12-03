#include "../../../Headers/StateMachine/Misc/CharacterBuilder.h"

bool CharacterBuilder::getIsBot() const {
    return _isBot;
}

const void CharacterBuilder::setIsBot(const bool state) {
    _isBot = state;
}

FACTION CharacterBuilder::getFaction() const {
    return _faction;
}

const void CharacterBuilder::setFaction(const FACTION faction) {
    _faction = faction;
}