#include "../../../../Headers/GameECS/Systems/Misc/FactionComparer.h"

FactionComparer::FactionComparer() {
    _weaknessMap = {
            { Faction::GREEN, Faction::RED},
            { Faction::YELLOW, Faction::GREEN},
            { Faction::RED, Faction::YELLOW}
    };
    _strengthMap = {
            { Faction::GREEN, Faction::YELLOW},
            { Faction::YELLOW, Faction::RED},
            { Faction::RED, Faction::GREEN}
    };
}

const Faction* FactionComparer::getWeakness(const Faction &faction) const {
    if (faction == Faction::WHITE) return nullptr;
    return &_weaknessMap.at(faction);
}

const Faction* FactionComparer::getStrength(const Faction &faction) const {
    if (faction == Faction::WHITE) return nullptr;
    return &_strengthMap.at(faction);
}

FactionComparer::~FactionComparer() = default;